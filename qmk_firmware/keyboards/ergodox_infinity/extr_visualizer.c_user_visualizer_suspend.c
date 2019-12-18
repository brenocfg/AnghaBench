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
struct TYPE_3__ {char* layer_text; int /*<<< orphan*/  target_lcd_color; int /*<<< orphan*/  current_lcd_color; } ;
typedef  TYPE_1__ visualizer_state_t ;
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  LCD_COLOR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCD_HUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCD_SAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_suspend_animation ; 
 int /*<<< orphan*/  start_keyframe_animation (int /*<<< orphan*/ *) ; 

void user_visualizer_suspend(visualizer_state_t* state) {
    state->layer_text = "Suspending...";
    uint8_t hue = LCD_HUE(state->current_lcd_color);
    uint8_t sat = LCD_SAT(state->current_lcd_color);
    state->target_lcd_color = LCD_COLOR(hue, sat, 0);
    start_keyframe_animation(&default_suspend_animation);
}