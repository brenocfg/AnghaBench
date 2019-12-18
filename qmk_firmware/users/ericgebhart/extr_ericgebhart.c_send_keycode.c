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
 int /*<<< orphan*/  KC_LSFT ; 
 int /*<<< orphan*/  KC_RSFT ; 
 int MOD_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHIFTED_KEY (int) ; 
 int SHIFTED_MODS (int) ; 
 int /*<<< orphan*/  UNSHIFTED_KEY (int) ; 
 int UNSHIFTED_MODS (int) ; 
 int /*<<< orphan*/  clear_mods () ; 
 int get_mods () ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_mods (int) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_mods (int) ; 

void send_keycode(uint8_t kc){
  uint8_t tmp_mods = get_mods();
  bool is_shifted = ( tmp_mods & (MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT)) );
  //uint8_t key[2][2] = key_translations[GR(kc)];
  // need to turn of the shift if it is on.
  unregister_mods((MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT)));
  if(is_shifted){
    register_mods(SHIFTED_MODS(kc));
    register_code(SHIFTED_KEY(kc));
    unregister_code(SHIFTED_KEY(kc));
    unregister_mods(SHIFTED_MODS(kc));
  } else{
    register_mods(UNSHIFTED_MODS(kc));
    register_code(UNSHIFTED_KEY(kc));
    unregister_code(UNSHIFTED_KEY(kc));
    unregister_mods(UNSHIFTED_MODS(kc));
  }
  clear_mods();
  register_mods(tmp_mods);
}