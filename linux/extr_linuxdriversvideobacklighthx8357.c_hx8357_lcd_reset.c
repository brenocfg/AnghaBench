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
struct lcd_device {int dummy; } ;
struct hx8357_data {int /*<<< orphan*/  reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 struct hx8357_data* lcd_get_data (struct lcd_device*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void hx8357_lcd_reset(struct lcd_device *lcdev)
{
	struct hx8357_data *lcd = lcd_get_data(lcdev);

	/* Reset the screen */
	gpio_set_value(lcd->reset, 1);
	usleep_range(10000, 12000);
	gpio_set_value(lcd->reset, 0);
	usleep_range(10000, 12000);
	gpio_set_value(lcd->reset, 1);

	/* The controller needs 120ms to recover from reset */
	msleep(120);
}