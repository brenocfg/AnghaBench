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
 int /*<<< orphan*/  KC_NLCK ; 
#define  _ADJUST 133 
#define  _FNL1 132 
#define  _GAMEMODE 131 
#define  _LOWER 130 
#define  _QWERTY 129 
#define  _RAISE 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnumlock ; 
 int /*<<< orphan*/  tap_code (int /*<<< orphan*/ ) ; 

uint32_t layer_state_set_user(uint32_t state) {
//  if(rgblight_get_mode() == 1) {
    switch (biton32(state)) {
    case _QWERTY:
        if(bnumlock) {
            tap_code(KC_NLCK);
        }
        break;
    case _LOWER:
        if(!bnumlock) {
            tap_code(KC_NLCK);
        }
        
        break;
    case _ADJUST:
        if(bnumlock) {
                tap_code(KC_NLCK);
        }
        break;
    case _RAISE:
        if(bnumlock) {
                tap_code(KC_NLCK);
        }
        break;
    case _FNL1:
        if(bnumlock) {
                tap_code(KC_NLCK);
        }
        break;
    case _GAMEMODE:
        break;
    default: //  for any other layers, or the default layer
        if(bnumlock) {
                tap_code(KC_NLCK);
        }
        
        break;
    }
 // }
  return state;
}