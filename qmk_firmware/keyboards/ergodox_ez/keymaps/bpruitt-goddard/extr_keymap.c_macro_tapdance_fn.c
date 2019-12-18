#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_7__ {int count; } ;
typedef  TYPE_2__ qk_tap_dance_state_t ;
struct TYPE_6__ {int pressed; } ;
struct TYPE_8__ {TYPE_1__ event; } ;
typedef  TYPE_3__ keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  DYN_MACRO_PLAY1 ; 
 int /*<<< orphan*/  DYN_REC_START1 ; 
 int /*<<< orphan*/  DYN_REC_STOP ; 
 int /*<<< orphan*/  current_layer_state ; 
 int /*<<< orphan*/  dprintf (char*,int) ; 
 int is_macro1_recording ; 
 int /*<<< orphan*/  layer_state_set_user (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_record_dynamic_macro (int /*<<< orphan*/ ,TYPE_3__*) ; 

void macro_tapdance_fn(qk_tap_dance_state_t *state, void *user_data) {
  uint16_t keycode;
  keyrecord_t record;
  dprintf("macro_tap_dance_fn %d\n", state->count);
  if (is_macro1_recording) {
    keycode = DYN_REC_STOP;
    is_macro1_recording = false;
    layer_state_set_user(current_layer_state);
  } else if (state->count == 1) {
    keycode = DYN_MACRO_PLAY1;
  } else {
    keycode = DYN_REC_START1;
    is_macro1_recording = true;
    layer_state_set_user(current_layer_state);
  }

  record.event.pressed = true;
  process_record_dynamic_macro(keycode, &record);
  record.event.pressed = false;
  process_record_dynamic_macro(keycode, &record);
}