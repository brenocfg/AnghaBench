#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
 int BACKLIGHT_LEVELS ; 
#define  COLEMAK 136 
#define  CONFIG 135 
 int /*<<< orphan*/  KC_LGUI ; 
#define  LEDDOWN 134 
#define  LEDUP 133 
#define  LLAYER 132 
#define  LLOCK 131 
#define  QWERTY 130 
#define  RLAYER 129 
#define  RLOCK 128 
 int /*<<< orphan*/  _COLEMAK ; 
 int /*<<< orphan*/  _CONFIG ; 
 int /*<<< orphan*/  _DUAL ; 
 int /*<<< orphan*/  _LLAYER ; 
 int /*<<< orphan*/  _QWERTY ; 
 int /*<<< orphan*/  _RLAYER ; 
 int /*<<< orphan*/  backlight_decrease () ; 
 int /*<<< orphan*/  backlight_increase () ; 
 int /*<<< orphan*/  backlight_toggle () ; 
 int blSteps ; 
 int configOn ; 
 void* get_backlight_level () ; 
 int layerBLStep ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int llocked ; 
 void* lockedBLLevel ; 
 void* momentaryLBLLevel ; 
 void* momentaryRBLLevel ; 
 int rlocked ; 
 int /*<<< orphan*/  set_single_persistent_default_layer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_tri_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
        configOn = false;
        if (momentaryRBLLevel != 0 || momentaryLBLLevel != 0){
          backlight_toggle();
        }
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
        configOn = false;
        if (momentaryRBLLevel != 0 || momentaryLBLLevel != 0){
          backlight_toggle();
        }
      }
      return false;
      break;
    case CONFIG:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_CONFIG);
        configOn = true;
        if (momentaryRBLLevel != 0 || momentaryLBLLevel != 0){
          backlight_toggle();
        }
      }
      return false;
      break;
    case RLAYER:
      if (record->event.pressed) {
        layer_on(_RLAYER);
        update_tri_layer(_RLAYER, _LLAYER, _DUAL);
        momentaryRBLLevel = get_backlight_level();
        if (momentaryRBLLevel != 0 || momentaryLBLLevel != 0){
          for (int i = 0; i < layerBLStep ; i++){
            backlight_increase();
          }
        }
      } else {
        unregister_code(KC_LGUI);
        layer_off(_RLAYER);
        update_tri_layer(_RLAYER, _LLAYER, _DUAL);
        if ( llocked == false && configOn == false ) {
          for (int i = 0; i < layerBLStep ; i++){
            backlight_decrease();
          }
        } else {
        }
        rlocked = false;
      }
      return false;
      break;
    case LLAYER:
      if (record->event.pressed) {
        layer_on(_LLAYER);
        update_tri_layer(_RLAYER, _LLAYER, _DUAL);
        momentaryLBLLevel = get_backlight_level();
        if (momentaryRBLLevel != 0 || momentaryLBLLevel != 0){
          for (int i = 0; i < layerBLStep ; i++){
            backlight_increase();
          }
        }
      } else {
        layer_off(_LLAYER);
        update_tri_layer(_RLAYER, _LLAYER, _DUAL);
        if ( rlocked == false && configOn == false ) {
          for (int i = 0; i < layerBLStep ; i++){
            backlight_decrease();
          }
        } else {
        }
        llocked = false;
      }
      return false;
      break;
    case RLOCK:
      if (record->event.pressed) {
        layer_on(_RLAYER);
        /* add logic to toggle backlight change when on a layer */
        if (rlocked == false && llocked == false){
          lockedBLLevel = get_backlight_level();
        }
        rlocked = true;
      } else {
      }
      return false;
      break;
    case LLOCK:
      if (record->event.pressed) {
        layer_on(_LLAYER);
        /* add logic to toggle backlight change when on a layer */
        if (rlocked == false && llocked == false){
          lockedBLLevel = get_backlight_level();
        }
        llocked = true;
      } else {
      }
      return false;
      break;
    case LEDUP:
      if (record->event.pressed) {
        for (int i = 0; i < (BACKLIGHT_LEVELS / blSteps ) ; i++ ){
          backlight_increase();
        }
      } else {
      }
      return false;
      break;
    case LEDDOWN:
      if (record->event.pressed) {
        for (int i = 0; i < (BACKLIGHT_LEVELS / blSteps ) ; i++ ){
          backlight_decrease();
        }
      } else {
      }
      return false;
      break;
  }
  return true;
}