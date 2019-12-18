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
typedef  int /*<<< orphan*/  visualizer_state_t ;
typedef  int /*<<< orphan*/  visualizer_keyboard_status_t ;

/* Variables and functions */
 int initial_update ; 
 int /*<<< orphan*/  led_test_animation ; 
 int /*<<< orphan*/  start_keyframe_animation (int /*<<< orphan*/ *) ; 

void update_user_visualizer_state(visualizer_state_t* state, visualizer_keyboard_status_t* prev_status) {
    // Add more tests, change the colors and layer texts here
    // Usually you want to check the high bits (higher layers first)
    // because that's the order layers are processed for keypresses
    // You can for check for example:
    // state->status.layer
    // state->status.default_layer
    // state->status.leds (see led.h for available statuses)

    if (initial_update) { initial_update=false; start_keyframe_animation(&led_test_animation); }
}