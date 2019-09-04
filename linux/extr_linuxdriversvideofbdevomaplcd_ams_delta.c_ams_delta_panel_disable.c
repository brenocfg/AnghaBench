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
struct lcd_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMS_DELTA_GPIO_PIN_LCD_NDISP ; 
 int /*<<< orphan*/  AMS_DELTA_GPIO_PIN_LCD_VBLEN ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ams_delta_panel_disable(struct lcd_panel *panel)
{
	gpio_set_value(AMS_DELTA_GPIO_PIN_LCD_VBLEN, 0);
	gpio_set_value(AMS_DELTA_GPIO_PIN_LCD_NDISP, 0);
}