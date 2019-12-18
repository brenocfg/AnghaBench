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

/* Variables and functions */
 int /*<<< orphan*/  current_hue ; 
 int /*<<< orphan*/  current_intensity ; 
 int /*<<< orphan*/  current_saturation ; 
 int /*<<< orphan*/  lcd_backlight_color (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcd_backlight_hal_init () ; 

void lcd_backlight_init(void) {
    lcd_backlight_hal_init();
    lcd_backlight_color(current_hue, current_saturation, current_intensity);
}