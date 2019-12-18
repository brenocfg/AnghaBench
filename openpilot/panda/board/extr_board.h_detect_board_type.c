#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  GPIOA ; 
 int /*<<< orphan*/  GPIOB ; 
 int /*<<< orphan*/  HW_TYPE_BLACK_PANDA ; 
 int /*<<< orphan*/  HW_TYPE_GREY_PANDA ; 
 int /*<<< orphan*/  HW_TYPE_PEDAL ; 
 int /*<<< orphan*/  HW_TYPE_UNKNOWN ; 
 int /*<<< orphan*/  HW_TYPE_UNO ; 
 int /*<<< orphan*/  HW_TYPE_WHITE_PANDA ; 
 int /*<<< orphan*/  PULL_DOWN ; 
 int /*<<< orphan*/  PULL_UP ; 
 int /*<<< orphan*/  board_black ; 
 int /*<<< orphan*/  board_grey ; 
 int /*<<< orphan*/  board_pedal ; 
 int /*<<< orphan*/  board_uno ; 
 int /*<<< orphan*/  board_white ; 
 int /*<<< orphan*/ * current_board ; 
 scalar_t__ detect_with_pull (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_type ; 
 int /*<<< orphan*/  puts (char*) ; 

void detect_board_type(void) {
  #ifdef PANDA
    // SPI lines floating: white (TODO: is this reliable?)
    if((detect_with_pull(GPIOA, 4, PULL_DOWN)) || (detect_with_pull(GPIOA, 5, PULL_DOWN)) || (detect_with_pull(GPIOA, 6, PULL_DOWN)) || (detect_with_pull(GPIOA, 7, PULL_DOWN))){
      hw_type = HW_TYPE_WHITE_PANDA;
      current_board = &board_white;
    } else if(detect_with_pull(GPIOA, 13, PULL_DOWN)) { // Rev AB deprecated, so no pullup means black. In REV C, A13 is pulled up to 5V with a 10K
      hw_type = HW_TYPE_GREY_PANDA;
      current_board = &board_grey;
    } else if(!detect_with_pull(GPIOB, 15, PULL_UP)) {
      hw_type = HW_TYPE_UNO;
      current_board = &board_uno;
    } else {
      hw_type = HW_TYPE_BLACK_PANDA;
      current_board = &board_black;
    }
  #else
    #ifdef PEDAL
      hw_type = HW_TYPE_PEDAL;
      current_board = &board_pedal;
    #else
      hw_type = HW_TYPE_UNKNOWN;
      puts("Hardware type is UNKNOWN!\n");
    #endif
  #endif
}