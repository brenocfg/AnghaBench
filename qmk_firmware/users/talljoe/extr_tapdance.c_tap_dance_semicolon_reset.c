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
struct TYPE_2__ {int semicolon; } ;

/* Variables and functions */
#define  DOUBLE_HOLD 133 
#define  DOUBLE_TAP 132 
 int /*<<< orphan*/  KC_SCLN ; 
 int /*<<< orphan*/  SEND_STRING (char*) ; 
#define  SINGLE_HOLD 131 
#define  SINGLE_TAP 130 
#define  SPECIAL 129 
#define  TRIPLE_TAP 128 
 int /*<<< orphan*/  _NUM ; 
 int /*<<< orphan*/  get_mods () ; 
 int /*<<< orphan*/  layer_invert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 TYPE_1__ tap_state ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

void tap_dance_semicolon_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (tap_state.semicolon) {
    case SINGLE_TAP: case DOUBLE_HOLD: unregister_code(KC_SCLN); break;
    case DOUBLE_TAP: {
      if (get_mods()) {
        SEND_STRING(";;"); // send normal when mods are pressed
      }
      else {
        SEND_STRING(";\n");
      }
      break;
    }
    case TRIPLE_TAP: {
      SEND_STRING(";\n\n");
    }
    case SPECIAL: layer_invert(_NUM); break;
    case SINGLE_HOLD: layer_off(_NUM); break;
  }
  tap_state.semicolon = 0;
}