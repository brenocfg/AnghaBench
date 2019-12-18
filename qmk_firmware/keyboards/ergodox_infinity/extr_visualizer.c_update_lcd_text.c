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
struct TYPE_6__ {scalar_t__ leds; scalar_t__ layer; scalar_t__ default_layer; } ;
struct TYPE_7__ {TYPE_1__ status; } ;
typedef  TYPE_2__ visualizer_state_t ;
struct TYPE_8__ {scalar_t__ leds; scalar_t__ layer; scalar_t__ default_layer; } ;
typedef  TYPE_3__ visualizer_keyboard_status_t ;

/* Variables and functions */
 scalar_t__ LCD_STATE_BITMAP_AND_LEDS ; 
 scalar_t__ LCD_STATE_LAYER_BITMAP ; 
 int /*<<< orphan*/  lcd_bitmap_animation ; 
 int /*<<< orphan*/  lcd_bitmap_leds_animation ; 
 scalar_t__ lcd_state ; 
 int /*<<< orphan*/  start_keyframe_animation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_keyframe_animation (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void update_lcd_text(visualizer_state_t* state, visualizer_keyboard_status_t* prev_status) {
    if (state->status.leds) {
        if (lcd_state != LCD_STATE_BITMAP_AND_LEDS ||
                state->status.leds != prev_status->leds ||
                state->status.layer != prev_status->layer ||
                state->status.default_layer != prev_status->default_layer) {

            // NOTE: that it doesn't matter if the animation isn't playing, stop will do nothing in that case
            stop_keyframe_animation(&lcd_bitmap_animation);

            lcd_state = LCD_STATE_BITMAP_AND_LEDS;
            // For information:
            // The logic in this function makes sure that this doesn't happen, but if you call start on an
            // animation that is already playing it will be restarted.
            start_keyframe_animation(&lcd_bitmap_leds_animation);
        }
    } else {
        if (lcd_state != LCD_STATE_LAYER_BITMAP ||
                state->status.layer != prev_status->layer ||
                state->status.default_layer != prev_status->default_layer) {

            stop_keyframe_animation(&lcd_bitmap_leds_animation);

            lcd_state = LCD_STATE_LAYER_BITMAP;
            start_keyframe_animation(&lcd_bitmap_animation);
        }
    }
}