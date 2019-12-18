#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int layer; } ;
struct TYPE_5__ {char* layer_text; void* target_lcd_color; TYPE_1__ status; } ;
typedef  TYPE_2__ visualizer_state_t ;
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLUE ; 
 int /*<<< orphan*/  Fade_in_all_leds ; 
 int /*<<< orphan*/  GREEN ; 
 void* LCD_COLOR (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  MAGENTA ; 
 int /*<<< orphan*/  OCEAN ; 
 int /*<<< orphan*/  ORANGE ; 
 int /*<<< orphan*/  RASPBERRY ; 
 int /*<<< orphan*/  RED ; 
 int /*<<< orphan*/  VIOLET ; 
 int /*<<< orphan*/  YELLOW ; 
 int /*<<< orphan*/  led_test_animation ; 
 int /*<<< orphan*/  start_keyframe_animation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_keyframe_animation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sweep_on_sweep_off_left_and_right ; 

__attribute__((used)) static void get_visualizer_layer_and_color(visualizer_state_t* state) {
    uint8_t saturation = 255;
    /* if (state->status.leds & (1u << USB_LED_CAPS_LOCK)) {
        saturation = 255;
    } */

    if (state->status.layer & 0x400) {
        state->target_lcd_color = LCD_COLOR(OCEAN, saturation, 0xFF);
        state->layer_text = "STENOGRAPHY";
    }
    else if (state->status.layer & 0x200) {
        state->target_lcd_color = LCD_COLOR(GREEN, saturation, 0xFF);
        state->layer_text = "FUNCTION";
    }
    else if (state->status.layer & 0x100) {
        state->target_lcd_color = LCD_COLOR(MAGENTA, saturation, 0xFF);
        state->layer_text = "Shortcuts Layer";
        stop_keyframe_animation(&sweep_on_sweep_off_left_and_right);
        start_keyframe_animation(&led_test_animation);
    }
    else    if (state->status.layer & 0x80) {
        state->target_lcd_color = LCD_COLOR(VIOLET, saturation, 0xFF);
        state->layer_text = "Plover";
    }
    else if (state->status.layer & 0x40) {
        state->target_lcd_color = LCD_COLOR(RASPBERRY, saturation, 0xFF);
        state->layer_text = "Mirrored Symbols";
    }
    else if (state->status.layer & 0x20) {
        state->target_lcd_color = LCD_COLOR(RED, saturation, 0xFF);
        state->layer_text = "Symbols";
    }
    else if (state->status.layer & 0x8) {
        state->target_lcd_color = LCD_COLOR(OCEAN, saturation, 0xFF);
        state->layer_text = "Mirrored Dvorak";
    }
    else if (state->status.layer & 0x4) {
        state->target_lcd_color = LCD_COLOR(BLUE, saturation, 0xFF);
        state->layer_text = "Dvorak";
        stop_keyframe_animation(&led_test_animation);
        start_keyframe_animation(&sweep_on_sweep_off_left_and_right);
    }
    else if (state->status.layer & 0x2) {
        state->target_lcd_color = LCD_COLOR(ORANGE, saturation, 0xFF);
        state->layer_text = "Mirrored Qwerty";
    }
    else {
        state->target_lcd_color = LCD_COLOR(YELLOW, saturation, 0xFF);
        state->layer_text = "Qwerty";
        stop_keyframe_animation(&led_test_animation);
        start_keyframe_animation(&Fade_in_all_leds);
    }
}