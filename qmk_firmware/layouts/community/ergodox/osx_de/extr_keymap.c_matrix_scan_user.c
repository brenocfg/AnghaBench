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
typedef  int uint8_t ;

/* Variables and functions */
#define  EGOS 132 
#define  MDIA 131 
#define  NUMB 130 
#define  SMLY 129 
#define  SYMB 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ergodox_board_led_off () ; 
 int /*<<< orphan*/  ergodox_right_led_1_off () ; 
 int /*<<< orphan*/  ergodox_right_led_1_on () ; 
 int /*<<< orphan*/  ergodox_right_led_2_off () ; 
 int /*<<< orphan*/  ergodox_right_led_2_on () ; 
 int /*<<< orphan*/  ergodox_right_led_3_off () ; 
 int /*<<< orphan*/  ergodox_right_led_3_on () ; 
 int /*<<< orphan*/  layer_state ; 

void matrix_scan_user(void) {

uint8_t layer = biton32(layer_state);

ergodox_board_led_off();
ergodox_right_led_1_off();
ergodox_right_led_2_off();
ergodox_right_led_3_off();
switch (layer) {

    case SYMB:
        ergodox_right_led_1_on();
        
        
        break;
    case MDIA:
        
        ergodox_right_led_2_on();
        
        break;
    case SMLY:
        
        
        ergodox_right_led_3_on();
        break;
    case NUMB:
        ergodox_right_led_1_on();
        
        ergodox_right_led_3_on();
        break;
    case EGOS:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        break;
default:
// none
break;
}

}