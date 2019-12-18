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
#define  _FUNCSHIFT 131 
#define  _FUNCTION 130 
#define  _MALT 129 
#define  _SHIFTED 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_state ; 
 int /*<<< orphan*/  set_led_blue ; 
 int /*<<< orphan*/  set_led_green ; 
 int /*<<< orphan*/  set_led_off ; 
 int /*<<< orphan*/  set_led_red ; 

void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);

    switch (layer) {
    	case _MALT:
    		set_led_off;
    		break;
        case _FUNCTION:
            set_led_blue;
            break;
        case _SHIFTED:
            set_led_red;
            break;
        case _FUNCSHIFT:
        	set_led_green;
        	break;
        default:
            break;
    }
}