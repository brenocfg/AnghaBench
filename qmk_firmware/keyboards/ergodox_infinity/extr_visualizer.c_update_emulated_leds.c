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
typedef  int /*<<< orphan*/  visualizer_user_data_t ;
struct TYPE_6__ {scalar_t__ user_data; } ;
struct TYPE_7__ {void* target_lcd_color; TYPE_1__ status; } ;
typedef  TYPE_2__ visualizer_state_t ;
struct TYPE_8__ {scalar_t__ user_data; } ;
typedef  TYPE_3__ visualizer_keyboard_status_t ;
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 scalar_t__ LCD_STATE_INITIAL ; 
 void* change_lcd_color_intensity (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ get_brightness (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ get_led_index_master (int /*<<< orphan*/ *) ; 
 scalar_t__ get_led_index_slave (int /*<<< orphan*/ *) ; 
 scalar_t__ get_secondary_led_index (int /*<<< orphan*/ *) ; 
 scalar_t__ is_serial_link_master () ; 
 scalar_t__ lcd_state ; 
 int /*<<< orphan*/ * led_emulation_colors ; 
 void* next_led_target_color ; 
 int /*<<< orphan*/  one_led_color ; 
 int /*<<< orphan*/  start_keyframe_animation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_keyframe_animation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  two_led_colors ; 

__attribute__((used)) static void update_emulated_leds(visualizer_state_t* state, visualizer_keyboard_status_t* prev_status) {
    visualizer_user_data_t* user_data_new = (visualizer_user_data_t*)state->status.user_data;
    visualizer_user_data_t* user_data_old = (visualizer_user_data_t*)prev_status->user_data;

    uint8_t new_index;
    uint8_t old_index;

    if (is_serial_link_master()) {
        new_index = get_led_index_master(user_data_new);
        old_index = get_led_index_master(user_data_old);
    }
    else {
        new_index = get_led_index_slave(user_data_new);
        old_index = get_led_index_slave(user_data_old);
    }
    uint8_t new_secondary_index = get_secondary_led_index(user_data_new);
    uint8_t old_secondary_index = get_secondary_led_index(user_data_old);

    uint8_t old_brightness = get_brightness(user_data_old, old_index);
    uint8_t new_brightness = get_brightness(user_data_new, new_index);

    uint8_t old_secondary_brightness = get_brightness(user_data_old, old_secondary_index);
    uint8_t new_secondary_brightness = get_brightness(user_data_new, new_secondary_index);

    if (lcd_state == LCD_STATE_INITIAL ||
            new_index != old_index ||
            new_secondary_index != old_secondary_index ||
            new_brightness != old_brightness ||
            new_secondary_brightness != old_secondary_brightness) {

        if (new_secondary_index != 0) {
            state->target_lcd_color = change_lcd_color_intensity(
                led_emulation_colors[new_index], new_brightness);
            next_led_target_color = change_lcd_color_intensity(
                led_emulation_colors[new_secondary_index], new_secondary_brightness);

            stop_keyframe_animation(&one_led_color);
            start_keyframe_animation(&two_led_colors);
        } else {
            state->target_lcd_color = change_lcd_color_intensity(
                led_emulation_colors[new_index], new_brightness);
            stop_keyframe_animation(&two_led_colors);
            start_keyframe_animation(&one_led_color);
        }
    }
}