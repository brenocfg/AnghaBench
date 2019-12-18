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
struct TYPE_3__ {int /*<<< orphan*/  target_lcd_color; int /*<<< orphan*/  current_lcd_color; } ;
typedef  TYPE_1__ visualizer_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  LCD_STATE_INITIAL ; 
 int /*<<< orphan*/  default_startup_animation ; 
 int /*<<< orphan*/  initial_color ; 
 int /*<<< orphan*/  lcd_backlight_brightness (int) ; 
 int /*<<< orphan*/  lcd_state ; 
 int /*<<< orphan*/  logo_background_color ; 
 int /*<<< orphan*/  start_keyframe_animation (int /*<<< orphan*/ *) ; 

void initialize_user_visualizer(visualizer_state_t* state) {
    // The brightness will be dynamically adjustable in the future
    // But for now, change it here.
    lcd_backlight_brightness(130);
    state->current_lcd_color = initial_color;
    state->target_lcd_color = logo_background_color;
    lcd_state = LCD_STATE_INITIAL;
    start_keyframe_animation(&default_startup_animation);
}