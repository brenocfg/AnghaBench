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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
#define  _ADJUST 131 
#define  _INTER 130 
#define  _NAV 129 
#define  _SYMB 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_setrgb_orange () ; 
 int /*<<< orphan*/  rgblight_setrgb_red () ; 
 int /*<<< orphan*/  rgblight_setrgb_springgreen () ; 
 int /*<<< orphan*/  rgblight_setrgb_teal () ; 
 int /*<<< orphan*/  rgblight_setrgb_yellow () ; 

uint32_t layer_state_set_user(uint32_t state) {
	switch (biton32(state)) {
		case _SYMB:
			rgblight_setrgb_orange();
			break;
		case _NAV:
			rgblight_setrgb_springgreen();
			break;
		case _INTER:
			rgblight_setrgb_teal();
			break;
		case _ADJUST:
			rgblight_setrgb_red();
			break;
		default: //  for any other layers, or the default layer
			rgblight_setrgb_yellow();
			break;
	}
	return state;
}