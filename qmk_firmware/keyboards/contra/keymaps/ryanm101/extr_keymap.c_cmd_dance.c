#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int count; } ;
typedef  TYPE_1__ qk_tap_dance_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  KC_4 ; 
 int /*<<< orphan*/  KC_DELETE ; 
 int /*<<< orphan*/  KC_ESC ; 
 int /*<<< orphan*/  KC_LALT ; 
 int /*<<< orphan*/  KC_LCTRL ; 
 int /*<<< orphan*/  KC_LGUI ; 
 int /*<<< orphan*/  KC_LSHIFT ; 
 int /*<<< orphan*/  MOD_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_mods (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_mods (int /*<<< orphan*/ ) ; 

void cmd_dance (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_mods(MOD_BIT(KC_LCTRL));
    register_mods(MOD_BIT(KC_LALT));
    register_code(KC_DELETE);
    unregister_mods(MOD_BIT(KC_LCTRL));
    unregister_mods(MOD_BIT(KC_LALT));
    unregister_code(KC_DELETE);
  } else if (state->count == 2) {
    register_mods(MOD_BIT(KC_LGUI));
    register_mods(MOD_BIT(KC_LALT));
    register_code(KC_ESC);
    unregister_mods(MOD_BIT(KC_LGUI));
    unregister_mods(MOD_BIT(KC_LALT));
    unregister_code(KC_ESC);
  } else if (state->count == 3) {
    register_mods(MOD_BIT(KC_LGUI));
    register_mods(MOD_BIT(KC_LSHIFT));
    register_code(KC_4);
    unregister_mods(MOD_BIT(KC_LGUI));
    unregister_mods(MOD_BIT(KC_LSHIFT));
    unregister_code(KC_4);
  }
}