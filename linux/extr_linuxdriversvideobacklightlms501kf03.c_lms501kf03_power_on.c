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
struct lms501kf03 {int /*<<< orphan*/  dev; int /*<<< orphan*/  ld; struct lcd_platform_data* lcd_pd; } ;
struct lcd_platform_data {int /*<<< orphan*/  reset_delay; int /*<<< orphan*/  (* reset ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  power_on_delay; int /*<<< orphan*/  (* power_on ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int lms501kf03_ldi_enable (struct lms501kf03*) ; 
 int lms501kf03_ldi_init (struct lms501kf03*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lms501kf03_power_on(struct lms501kf03 *lcd)
{
	int ret = 0;
	struct lcd_platform_data *pd;

	pd = lcd->lcd_pd;

	if (!pd->power_on) {
		dev_err(lcd->dev, "power_on is NULL.\n");
		return -EINVAL;
	}

	pd->power_on(lcd->ld, 1);
	msleep(pd->power_on_delay);

	if (!pd->reset) {
		dev_err(lcd->dev, "reset is NULL.\n");
		return -EINVAL;
	}

	pd->reset(lcd->ld);
	msleep(pd->reset_delay);

	ret = lms501kf03_ldi_init(lcd);
	if (ret) {
		dev_err(lcd->dev, "failed to initialize ldi.\n");
		return ret;
	}

	ret = lms501kf03_ldi_enable(lcd);
	if (ret) {
		dev_err(lcd->dev, "failed to enable ldi.\n");
		return ret;
	}

	return 0;
}