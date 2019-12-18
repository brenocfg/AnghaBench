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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  _ADJUST ; 
#define  _DPAD 130 
#define  _FN1 129 
 int /*<<< orphan*/  _LOWER ; 
#define  _QWERTY 128 
 int /*<<< orphan*/  _RAISE ; 
 int /*<<< orphan*/  backlight_set (int) ; 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_tri_layer_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint32_t layer_state_set_user(uint32_t state) {

  // LED control, lighting up when Fn layer is activated
  
  state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
  
  switch (biton32(state)) {
    case _QWERTY:
      backlight_set(0);
      break;
    case _FN1:
      backlight_set(3);
      break;
	case _DPAD:
      backlight_set(3);
      break;
  }

  return state;
}