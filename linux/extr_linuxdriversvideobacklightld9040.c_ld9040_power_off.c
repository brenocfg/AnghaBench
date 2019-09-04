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
struct ld9040 {int /*<<< orphan*/  dev; struct lcd_platform_data* lcd_pd; } ;
struct lcd_platform_data {int /*<<< orphan*/  power_off_delay; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int ld9040_ldi_disable (struct ld9040*) ; 
 int /*<<< orphan*/  ld9040_regulator_disable (struct ld9040*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ld9040_power_off(struct ld9040 *lcd)
{
	int ret;
	struct lcd_platform_data *pd;

	pd = lcd->lcd_pd;

	ret = ld9040_ldi_disable(lcd);
	if (ret) {
		dev_err(lcd->dev, "lcd setting failed.\n");
		return -EIO;
	}

	msleep(pd->power_off_delay);

	/* lcd power off */
	ld9040_regulator_disable(lcd);

	return 0;
}