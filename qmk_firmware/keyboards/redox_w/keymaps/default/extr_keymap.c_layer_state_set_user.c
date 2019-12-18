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
typedef  int /*<<< orphan*/  layer_state_t ;

/* Variables and functions */
#define  _ADJUST 131 
#define  _NAV 130 
#define  _QWERTY 129 
#define  _SYMB 128 
 int get_highest_layer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_led_blue ; 
 int /*<<< orphan*/  set_led_green ; 
 int /*<<< orphan*/  set_led_off ; 
 int /*<<< orphan*/  set_led_red ; 

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _QWERTY:
            set_led_off;
            break;
        case _SYMB:
            set_led_green;
            break;
        case _NAV:
            set_led_blue;
            break;
        case _ADJUST:
            set_led_red;
            break;
        default:
            break;
    }
  return state;
}