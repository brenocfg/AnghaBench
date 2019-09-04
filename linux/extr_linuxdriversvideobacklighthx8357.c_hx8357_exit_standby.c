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

/* Variables and functions */
 int /*<<< orphan*/  HX8357_EXIT_SLEEP_MODE ; 
 int /*<<< orphan*/  HX8357_SET_DISPLAY_ON ; 
 int hx8357_spi_write_byte (struct lcd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int hx8357_exit_standby(struct lcd_device *lcdev)
{
	int ret;

	ret = hx8357_spi_write_byte(lcdev, HX8357_EXIT_SLEEP_MODE);
	if (ret < 0)
		return ret;

	/*
	 * The controller needs 120ms when exiting from sleep mode before we
	 * can send the command to enter in sleep mode
	 */
	msleep(120);

	ret = hx8357_spi_write_byte(lcdev, HX8357_SET_DISPLAY_ON);
	if (ret < 0)
		return ret;

	return 0;
}