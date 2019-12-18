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
typedef  int /*<<< orphan*/  layer_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  default_layer_state_set_keymap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_layer_state_set_rgb (int /*<<< orphan*/ ) ; 

layer_state_t default_layer_state_set_user(layer_state_t state) {
    state = default_layer_state_set_keymap(state);
#if 0
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
  state = default_layer_state_set_rgb(state);
#    endif  // RGBLIGHT_ENABLE
#endif
    return state;
}