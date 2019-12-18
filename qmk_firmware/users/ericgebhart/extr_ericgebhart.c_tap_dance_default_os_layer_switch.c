#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  count; } ;
typedef  TYPE_1__ qk_tap_dance_state_t ;
struct TYPE_6__ {int mods; } ;

/* Variables and functions */
 int /*<<< orphan*/  KC_LSFT ; 
 int /*<<< orphan*/  KC_RSFT ; 
 int MOD_BIT (int /*<<< orphan*/ ) ; 
 TYPE_4__* keyboard_report ; 
 int on_qwerty () ; 
 int /*<<< orphan*/  reset_tap_dance (TYPE_1__*) ; 
 int /*<<< orphan*/  switch_default_layer_on_bepo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  switch_default_layer_on_qwerty (int /*<<< orphan*/ ) ; 

void tap_dance_default_os_layer_switch (qk_tap_dance_state_t *state, void *user_data) {
  //uint8_t shifted = (get_mods() & MOD_BIT(KC_LSFT|KC_RSFT));
  bool shifted = ( keyboard_report->mods & (MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT)) );
  int qwerty = on_qwerty();


  // shifted, choose between layers on the other software keyboard
  if(shifted){
    if (qwerty)
      switch_default_layer_on_bepo(state->count);
    else
          switch_default_layer_on_qwerty(state->count);

    // not shifted, choose between layers on the same software keyboard
  } else {
    if (qwerty)
      switch_default_layer_on_qwerty(state->count);
    else
      switch_default_layer_on_bepo(state->count);
  }

  reset_tap_dance(state);
}