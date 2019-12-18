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
 int /*<<< orphan*/  KC_NLCK ; 
#define  _ADJUST 134 
#define  _FNL1 133 
#define  _GAMEMODE 132 
#define  _LOWER 131 
#define  _MOUSE 130 
#define  _QWERTY 129 
#define  _RAISE 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnumlock ; 
 int /*<<< orphan*/  rgbflag (int,int,int) ; 
 int /*<<< orphan*/  rgblight_mode (int) ; 
 int /*<<< orphan*/  tap_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  workmode ; 

layer_state_t layer_state_set_user(layer_state_t state) {
//  if(rgblight_get_mode() == 1) {
    switch (biton32(state)) {
    case _QWERTY:
        if(!workmode){
            rgblight_mode(9);
        }
        else if(workmode){
            rgblight_mode(1);
            rgbflag(0x00,  0x00, 0x00);
        }
        if(bnumlock) {
            tap_code(KC_NLCK);
        }
        break;
    case _LOWER:
            rgblight_mode(1);
        if(!bnumlock) {
            tap_code(KC_NLCK);
        }
        rgbflag(0xFF,  0x00, 0x00);
        
        break;
    case _ADJUST:
        rgblight_mode(1);
        rgbflag(0xFF,  0xFF, 0xFF);
        if(bnumlock) {
                tap_code(KC_NLCK);
        }
        break;
    case _RAISE:
        rgblight_mode(1);
        rgbflag(0x00,  0xFF, 0x00);
        if(bnumlock) {
                tap_code(KC_NLCK);
        }
        break;
    case _FNL1:
        rgblight_mode(1);
        rgbflag(0x00,  0x00, 0xFF);
        if(bnumlock) {
                tap_code(KC_NLCK);
        }
        break;
    case _GAMEMODE:
            rgblight_mode(1);
            rgbflag(0xFF,  0x00, 0xFF);
        break;
    case _MOUSE:
        rgblight_mode(1);
        rgbflag(0x00,  0xFF, 0xFF);
        if(bnumlock) {
                tap_code(KC_NLCK);
        }
        break;
    default: //  for any other layers, or the default layer
        rgblight_mode(1);
        if(bnumlock) {
            tap_code(KC_NLCK);
        }        
        rgbflag(0xFF,  0xFF, 0xFF);
        break;
    }
 // }
  return state;
}