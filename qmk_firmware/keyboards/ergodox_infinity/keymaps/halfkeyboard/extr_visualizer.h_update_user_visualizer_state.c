#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ target_lcd_color; char* layer_text; } ;
typedef  TYPE_1__ visualizer_state_t ;
typedef  int /*<<< orphan*/  visualizer_keyboard_status_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  color_animation ; 
 int /*<<< orphan*/  get_visualizer_layer_and_color (TYPE_1__*) ; 
 scalar_t__ initial_update ; 
 int /*<<< orphan*/  lcd_layer_display ; 
 int /*<<< orphan*/  start_keyframe_animation (int /*<<< orphan*/ *) ; 

void update_user_visualizer_state(visualizer_state_t* state, visualizer_keyboard_status_t* prev_status) {
    // Add more tests, change the colors and layer texts here
    // Usually you want to check the high bits (higher layers first)
    // because that's the order layers are processed for keypresses
    // You can for check for example:
    // state->status.layer
    // state->status.default_layer
    // state->status.leds (see led.h for available statuses)

    uint32_t prev_color = state->target_lcd_color;
    const char* prev_layer_text = state->layer_text;

    get_visualizer_layer_and_color(state);

    if (initial_update || prev_color != state->target_lcd_color) {
        start_keyframe_animation(&color_animation);
    }

    if (initial_update || prev_layer_text != state->layer_text) {
        start_keyframe_animation(&lcd_layer_display);
    }
    // You can also stop existing animations, and start your custom ones here
    // remember that you should normally have only one animation for the LCD
    // and one for the background. But you can also combine them if you want.

}