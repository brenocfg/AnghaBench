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
 int biton32 (int /*<<< orphan*/ ) ; 
#define  lower 129 
#define  raise 128 
 int /*<<< orphan*/  rgblight_mode_noeeprom (int) ; 
 int /*<<< orphan*/  rgblight_setrgb (int,int,int) ; 

uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
    case raise:
        rgblight_mode_noeeprom(1);
        rgblight_setrgb(0xc7, 0x00, 0xf4);
        break;
    case lower:
        rgblight_mode_noeeprom(1);
        rgblight_setrgb(0x00, 0xa3, 0x0d);
        break;
    default: // for any other layers, or the default layer
        rgblight_mode_noeeprom(5);
        rgblight_setrgb(0xFF, 0xB6, 0x00);
        break;
    }
  return state;
}