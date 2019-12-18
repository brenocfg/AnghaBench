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
#define  _LAYERS 134 
#define  _MOUSE 133 
#define  _NUMBERS 132 
#define  _PUNCT 131 
#define  _QWERTY 130 
#define  _UNICODE 129 
#define  _WORKMAN 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_state ; 
 int /*<<< orphan*/  set_led_blue ; 
 int /*<<< orphan*/  set_led_cyan ; 
 int /*<<< orphan*/  set_led_green ; 
 int /*<<< orphan*/  set_led_off ; 
 int /*<<< orphan*/  set_led_red ; 
 int /*<<< orphan*/  set_led_yellow ; 

void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);

    switch (layer) {
    	case _QWERTY:
    	case _WORKMAN:
    		set_led_off;
    		break;
        case _NUMBERS:
            set_led_blue;
            break;
        case _PUNCT:
            set_led_red;
            break;
        case _MOUSE:
            set_led_green;
            break;
        case _LAYERS:
            set_led_yellow;
            break;
        case _UNICODE:
            set_led_cyan;
            break;
        default:
            break;
   }
}