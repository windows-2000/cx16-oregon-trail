#include <cx16.h>
#include <stdio.h>
#include <stdint.h>
#include <conio.h>
#include "vera.h"

void __fastcall__ clear_screen(void);

// inline assembly for scanning keycode from keyboard
#define scan_key_code(a) \
__asm__ ("jsr $FFE4"); \
__asm__ ("sta %v", a);

// any key to continue
#define anykey()\
printf("\n-=-=- any key to continue -=-=-\n");\
while(1) {\
    scan_key_code(keycode);\
    if(keycode != 0){\
      break;\
    }\
  };

unsigned char keycode;

unsigned int A;// = AMOUNT SPENT ON ANIMALS
unsigned int B;// = AMOUNT SPENT ON AMMUNITION
unsigned int B1;// = ACTUAL RESPONSE TIME FOR INPUTTING "BANG"
unsigned int B3;// = CLOCK TIME AT START OF INPUTTING "BANG"
unsigned int C;// = AMOUNT SPENT ON CLOTHING
unsigned int C1;// = FLAG FOR INSUFFICIENT CLOTHING IN COLD WEATHER
unsigned int CD;// = YES/N0 RESPONSE TO QUESTIONS
unsigned int D1;// = COUNTER IN GENERATING EVENTS
unsigned int D3;// = TURN NUMBER FOR SETTING DATE
unsigned int D4;// = CURRENT DATE
unsigned int D9;// = CHOICE OF SHOOTING EXPERTISE LEVEL
unsigned int E;// = CHOICE OF EATING
unsigned int F;// = AMOUNT SPENT ON FOOD
unsigned int F1;// = FLAG FOR CLEARING SOUTH PASS
unsigned int F2;// = FLAG FOR CLEARING BLUE MOUNTAINS
unsigned int F9;// = FRACTION OF 2 WEEKS TRAVELED ON FINAL TURN
unsigned int K8;// = FLAG FOR INJURY
unsigned int L1;// = FLAG FOR BLIZZARD
unsigned int M;// = TOTAL MILEAGE WHOLE TRIP
unsigned int M1;// = AMOUNT SPENT ON MISCELLANEOUS SUPPLIES
unsigned int M2;// = TOTAL MILEAGE UP THROUGH PREVIOUS TURN
unsigned int M9;// = FLAG FOR CLEARING SOUTH PASS IN SETTING MILEAGE
unsigned int P;// = AMOUNT SPENT ON ITEMS AT FORT
unsigned int R1;// = RANDOM NUMBER IN CHOOSING EVENTS
unsigned int S4;// = FLAG FOR ILLNESS
unsigned int S5;// = ""HOSTILITY OF RIDERS"" FACTOR
unsigned int S6;// = SHOOTING WORD SELECTOR
unsigned int SD;// = VARIATIONS OF SHOOTING WORD
unsigned int T;// = CASH LEFT OVER AFTER INITIAL PURCHASES
unsigned int T1;// = CHOICE OF TACTICS WHEN ATTACKED
unsigned int X;// = CHOICE OF ACTION FOR EACH TURN
unsigned int X1;// = FLAG FOR FORT OPTION

void titleLoop() {
  clrscr();
  printf("\nDO YOU NEED INSTRUCTIONS (YES/NO)?\n\n");
  while(1) {
    scan_key_code(keycode);
    // If Y or y is pressed
    if(keycode == 217 || keycode == 89){
      clrscr();
      printf("\nTHIS PROGRAM SIMULATES A TRIP OVER THE OREGON TRAIL FROM\n");
      printf("INDEPENDENCE, MISSOURI TO OREGON CITY, OREGON IN 1847.\n");
      printf("YOUR FAMILY OF FIVE WILL COVER THE 2040 MILE OREGON TRAIL\n");
      printf("IN 5-6 MONTHS --- IF YOU MAKE IT ALIVE.\n\n");
      printf("YOU HAD SAVED $900 TO SPEND FOR THE TRIP, AND YOU'VE JUST\n");
      printf("   PAID $200 FOR A WAGON.\n\n");
      printf("YOU WILL NEED TO SPEND THE REST OF YOUR MONEY ON THE\n");
      printf("   FOLLOWING ITEMS:\n\n");
      printf("     OXEN - YOU CAN SPEND $200-$300 ON YOUR TEAM\n");
      printf("            THE MORE YOU SPEND, THE FASTER YOU'LL GO\n");
      printf("               BECAUSE YOU'LL HAVE BETTER ANIMALS\n\n");
      printf("     FOOD - THE MORE YOU HAVE, THE LESS CHANCE THERE\n");
      printf("               IS OF GETTING SICK\n\n");
      printf("     AMMUNITION - $1 BUYS A BELT OF 50 BULLETS\n");
      printf("            YOU WILL NEED BULLETS FOR ATTACKS BY ANIMALS\n");
      printf("               AND BANDITS, AND FOR HUNTING FOOD\n\n");
      printf("     CLOTHING - THIS IS ESPECIALLY IMPORTANT FOR THE COLD\n");
      printf("               WEATHER YOU WILL ENCOUNTER WHEN CROSSING\n");
      printf("               THE MOUNTAINS\n\n");
      printf("     MISCELLANEOUS SUPPLIES - THIS INCLUDES MEDICINE AND\n");
      printf("               OTHER THINGS YOU WILL NEED FOR SICKNESS\n");
      printf("               AND EMERGENCY REPAIRS\n\n");
      printf("YOU CAN SPEND ALL YOUR MONEY BEFORE YOU START YOUR TRIP -\n");
      printf("OR YOU CAN SAVE SOME OF YOUR CASH TO SPEND AT FORTS ALONG\n");
      printf("THE WAY WHEN YOU RUN LOW. HOWEVER, ITEMS COST MORE AT\n");
      printf("THE FORTS. YOU CAN ALSO GO HUNTING ALONG THE WAY TO GET\n");
      printf("MORE FOOD.\n");
      printf("WHENEVER YOU HAVE TO USE YOUR TRUSTY RIFLE ALONG THE WAY,\n");
      printf("YOU WILL BE TOLD TO TYPE IN A WORD (ONE THAT SOUNDS LIKE A \n");
      printf("GUN SHOT). THE FASTER YOU TYPE IN THAT WORD AND HIT THE\n");
      printf("\"RETURN\" KEY, THE BETTER LUCK YOU'LL HAVE WITH YOUR GUN.\n\n");
      printf("AT EACH TURN, ALL ITEMS ARE SHOWN IN DOLLAR AMOUNTS\n");
      printf("EXCEPT BULLETS\n");
      printf("WHEN ASKED TO ENTER MONEY AMOUNTS, DON'T USE A \"$\".\n\n");
      printf("GOOD LUCK!!!\n");
      break;
    } else if(keycode != 0){
      break;
    }
  }
  anykey();
}

void setupLoop() {
  clrscr();
  printf("\nHOW GOOD A SHOT ARE YOU WITH YOUR RIFLE?\n");
  printf("  (1) ACE MARKSMAN,  (2) GOOD SHOT,  (3) FAIR TO MIDDLIN'\n");
  printf("         (4) NEED MORE PRACTICE,  (5) SHAKY KNEES\n");
  printf("ENTER ONE OF THE ABOVE -- THE BETTER YOU CLAIM YOU ARE, THE\n");
  printf("FASTER YOU'LL HAVE TO BE WITH YOUR GUN TO BE SUCCESSFUL.\n");
  while(1) {
    scan_key_code(keycode);
    // If a number 0 to 5 is pressed
    if(keycode >= 48 && keycode <= 53){
      D9 = (int)keycode - 48;
      printf("Setting expertise level %u", D9);
      break;
    }
  }
  anykey();
  while(A <200 || A > 930){
    clrscr();
    printf("\nHOW MUCH DO YOU WANT TO SPEND ON YOUR OXEN TEAM?\n");
    scanf("%d", &A);
    if(A > 0 && A < 200){
      printf("NOT ENOUGH!");
      A = 0;
      anykey();
    }  else if(A > 300){
      printf("TOO MUCH!");
      A = 0;
      anykey();
    } else{
      break;
    }
  }
  printf("Setting amount spent on animals to %u", A);
  anykey();

  while(F <200 || F > 930){
    clrscr();
    printf("\nHOW MUCH DO YOU WANT TO SPEND ON FOOD?\n");
    scanf("%d", &F);
    if(F == 0){
      printf("IMPOSSIBLE");
      F = 0;
      anykey();
    }
    else{
      break;
    }
  }
  printf("Setting amount spent on food to %u", F);
  anykey();
}

void main(void) {
  // VERA.control = 0;
  // VERA.display.video |= LAYER1_ENABLED;
  // VERA.display.hscale = SCALE_4x;
  // VERA.display.vscale = SCALE_4x;
  // VERA.layer0.config = 0x0;  // Disable Layer 0
  // VERA.layer1.config = LAYER_CONFIG_8BPP | LAYER_CONFIG_BITMAP ;         	// 128x64 map, color depth 1
  // VERA.layer1.mapbase = MAP_BASE_ADDR(0x0);                               // Map base at 0x00000
  // VERA.layer1.tilebase = 0;  												// Tile base at 0x10000, 8x8 tiles
  // videomode(VIDEOMODE_40x30);
  //clear_screen();
  titleLoop();
  setupLoop();
}