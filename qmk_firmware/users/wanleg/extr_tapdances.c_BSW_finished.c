#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qk_tap_dance_state_t ;
struct TYPE_2__ {int state; } ;

/* Variables and functions */
 TYPE_1__ BSWtap_state ; 
#define  DOUBLE_HOLD 131 
#define  DOUBLE_TAP 130 
 int /*<<< orphan*/  KC_C ; 
 int /*<<< orphan*/  KC_ENTER ; 
 int /*<<< orphan*/  KC_LCTRL ; 
 int /*<<< orphan*/  PLAY_SONG (int /*<<< orphan*/ ) ; 
#define  SINGLE_HOLD 129 
#define  SINGLE_TAP 128 
 int cur_dance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lyrdown_song ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_keyboard () ; 
 int /*<<< orphan*/  set_single_persistent_default_layer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_all_notes () ; 

void BSW_finished (qk_tap_dance_state_t *state, void *user_data) {
  BSWtap_state.state = cur_dance(state);
  switch (BSWtap_state.state) {
    case SINGLE_TAP: register_code(KC_ENTER); break;
    case SINGLE_HOLD:
      set_single_persistent_default_layer(0);
      #ifdef AUDIO_ENABLE
        stop_all_notes();
        PLAY_SONG(lyrdown_song);
      #endif
      break;
    case DOUBLE_TAP:
	  register_code(KC_LCTRL);
      register_code(KC_C);
	  break;
	case DOUBLE_HOLD:
	  reset_keyboard();
	  break; //register this keycode when button is tapped and then held
  }
}