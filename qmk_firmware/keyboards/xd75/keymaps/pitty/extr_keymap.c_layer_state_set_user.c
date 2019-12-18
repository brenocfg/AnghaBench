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
#define  _GAME 130 
#define  _LOWER 129 
#define  _RAISE 128 
 int get_highest_layer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_mode (int) ; 
 int /*<<< orphan*/  rgblight_setrgb (int,int,int) ; 

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _RAISE:
        rgblight_setrgb (0xC3,  0xFF, 0xFF);
		rgblight_mode(5);
        break;
    case _LOWER:
        rgblight_setrgb (0xFF, 0xFF, 0xFF);
		rgblight_mode(5);
        break;
    case _GAME:
        rgblight_mode(8);
        break;
    default: //  for any other layers, or the default layer
        rgblight_mode(14);
        break;
    }
  return state;
}