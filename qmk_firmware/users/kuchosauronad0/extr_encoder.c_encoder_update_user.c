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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  KC_0 ; 
 int /*<<< orphan*/  KC_1 ; 
 int MOD_MASK_ALT ; 
 int MOD_MASK_CTRL ; 
 int MOD_MASK_GUI ; 
 int MOD_MASK_SHIFT ; 
 int /*<<< orphan*/  clear_mods () ; 
 int /*<<< orphan*/ ** encoder_actions ; 
 int get_mods () ; 
 int /*<<< orphan*/  set_mods (int) ; 
 int /*<<< orphan*/  tap_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tap_code16 (int /*<<< orphan*/ ) ; 

void encoder_update_user(uint8_t index, bool clockwise) {
  static uint16_t kc;
  uint8_t temp_mod = get_mods();
  if (index == 0) { /* first encoder */
    if (clockwise) {
      //if (temp_mod & MOD_BIT(KC_HYPR)){ // TODO: not how this works, only registers CTRL
        if ((temp_mod & MOD_MASK_CTRL) && (temp_mod & MOD_MASK_SHIFT) && (temp_mod & MOD_MASK_ALT) && (temp_mod & MOD_MASK_GUI)) { // HYPER
          kc = encoder_actions[0][8];
        } else if ( (temp_mod & MOD_MASK_SHIFT) && (temp_mod & MOD_MASK_ALT) ) {  // ALT+SHIFT
          kc = encoder_actions[0][7];
        } else if ( (temp_mod & MOD_MASK_SHIFT) && (temp_mod & MOD_MASK_CTRL) ) { // CTRL+SHIFT
          kc = encoder_actions[0][6];
        } else if ( (temp_mod & MOD_MASK_CTRL) && (temp_mod & MOD_MASK_ALT) ) {   // CTRL+ALT
          kc = encoder_actions[0][5];
        } else if (temp_mod & MOD_MASK_GUI) {   // GUI
          kc = encoder_actions[0][4];
        } else if (temp_mod & MOD_MASK_SHIFT) { // SHIFT
          kc = encoder_actions[0][3];
        } else if (temp_mod & MOD_MASK_ALT) {   // ALT
          kc = encoder_actions[0][2];
        } else if (temp_mod & MOD_MASK_CTRL) {  // CTRL
          kc = encoder_actions[0][1];
        } else {                                // None
          kc = encoder_actions[0][0];
        }
      } else { // Counter Clockwise
        if ((temp_mod & MOD_MASK_CTRL) && (temp_mod & MOD_MASK_SHIFT) && (temp_mod & MOD_MASK_ALT) && (temp_mod & MOD_MASK_GUI)) { // HYPER
          kc = encoder_actions[1][8];
        } else if ( (temp_mod & MOD_MASK_SHIFT) && (temp_mod & MOD_MASK_ALT) ) {  // ALT+SHIFT
          kc = encoder_actions[1][7];
        } else if ( (temp_mod & MOD_MASK_SHIFT) && (temp_mod & MOD_MASK_CTRL) ) { // CTRL+SHIFT
          kc = encoder_actions[1][6];
        } else if ( (temp_mod & MOD_MASK_CTRL) && (temp_mod & MOD_MASK_ALT) ) {   // CTRL+ALT
          kc = encoder_actions[1][5];
        } else if (temp_mod & MOD_MASK_GUI) {   // GUI
          kc = encoder_actions[1][4];
        } else if (temp_mod & MOD_MASK_SHIFT) { // SHIFT
          kc = encoder_actions[1][3];
        } else if (temp_mod & MOD_MASK_ALT) {   // ALT
          kc = encoder_actions[1][2];
        } else if (temp_mod & MOD_MASK_CTRL) {  // CTRL
          kc = encoder_actions[1][1];
        } else {                                // None
          kc = encoder_actions[1][0];
        }
      }
        clear_mods();
        tap_code16(kc);
        set_mods(temp_mod);
  } else if (index == 1){ // second Encoder
      if (clockwise) {
        tap_code(KC_0);
      } else{
        tap_code(KC_1);
      }
  }
}