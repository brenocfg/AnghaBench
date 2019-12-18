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
typedef  scalar_t__ uint8_t ;
struct TYPE_3__ {int count; } ;
typedef  TYPE_1__ qk_tap_dance_state_t ;

/* Variables and functions */
 scalar_t__ _GAMING ; 
 scalar_t__ _QWERTY ; 
 scalar_t__ biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_off (scalar_t__) ; 
 int /*<<< orphan*/  layer_on (scalar_t__) ; 
 int /*<<< orphan*/  layer_state ; 
 int /*<<< orphan*/  rgblight_mode_noeeprom (int) ; 

void dance_game (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {

  } else if (state->count == 2) {

  } else if (state->count == 3) {
    uint8_t layer = biton32(layer_state);
    if (layer == _QWERTY) {
        layer_off(_QWERTY);
        layer_on(_GAMING);
        // swirling rgb
        rgblight_mode_noeeprom(12);
    } else {
        layer_off(_GAMING);
        layer_on(_QWERTY);
        rgblight_mode_noeeprom(1);
    }
  }
}