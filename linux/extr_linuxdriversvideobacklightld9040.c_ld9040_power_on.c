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
struct ld9040 {int /*<<< orphan*/  dev; int /*<<< orphan*/  ld; struct lcd_platform_data* lcd_pd; } ;
struct lcd_platform_data {int /*<<< orphan*/  reset_delay; int /*<<< orphan*/  (* reset ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int ld9040_ldi_enable (struct ld9040*) ; 
 int ld9040_ldi_init (struct ld9040*) ; 
 int /*<<< orphan*/  ld9040_regulator_enable (struct ld9040*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ld9040_power_on(struct ld9040 *lcd)
{
	int ret = 0;
	struct lcd_platform_data *pd;

	pd = lcd->lcd_pd;

	/* lcd power on */
	ld9040_regulator_enable(lcd);

	if (!pd->reset) {
		dev_err(lcd->dev, "reset is NULL.\n");
		return -EINVAL;
	}

	pd->reset(lcd->ld);
	msleep(pd->reset_delay);

	ret = ld9040_ldi_init(lcd);
	if (ret) {
		dev_err(lcd->dev, "failed to initialize ldi.\n");
		return ret;
	}

	ret = ld9040_ldi_enable(lcd);
	if (ret) {
		dev_err(lcd->dev, "failed to enable ldi.\n");
		return ret;
	}

	return 0;
}