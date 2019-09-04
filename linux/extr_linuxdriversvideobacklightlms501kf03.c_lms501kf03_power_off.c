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
struct lms501kf03 {int /*<<< orphan*/  ld; int /*<<< orphan*/  dev; struct lcd_platform_data* lcd_pd; } ;
struct lcd_platform_data {int /*<<< orphan*/  (* power_on ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  power_off_delay; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int lms501kf03_ldi_disable (struct lms501kf03*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lms501kf03_power_off(struct lms501kf03 *lcd)
{
	int ret = 0;
	struct lcd_platform_data *pd;

	pd = lcd->lcd_pd;

	ret = lms501kf03_ldi_disable(lcd);
	if (ret) {
		dev_err(lcd->dev, "lcd setting failed.\n");
		return -EIO;
	}

	msleep(pd->power_off_delay);

	pd->power_on(lcd->ld, 0);

	return 0;
}