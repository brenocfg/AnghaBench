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
struct TYPE_3__ {scalar_t__ pressed; } ;
typedef  TYPE_1__ qk_tap_dance_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  KC_LGUI ; 
 int /*<<< orphan*/  KC_SPC ; 
 int MOD_BIT (int /*<<< orphan*/ ) ; 
 int get_mods () ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int spam_space ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

void tap_space_spam_finished(qk_tap_dance_state_t *state, void *user_data) {
    if(get_mods() & (MOD_BIT(KC_LGUI))){
      return;
    }
    if(state->pressed){
        spam_space = true;
    }
    register_code(KC_SPC);
    unregister_code(KC_SPC);
}