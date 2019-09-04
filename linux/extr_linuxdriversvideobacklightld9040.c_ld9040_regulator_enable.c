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
struct ld9040 {int enabled; int /*<<< orphan*/  lock; struct lcd_platform_data* lcd_pd; } ;
struct lcd_platform_data {int /*<<< orphan*/  power_on_delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  supplies ; 

__attribute__((used)) static void ld9040_regulator_enable(struct ld9040 *lcd)
{
	int ret = 0;
	struct lcd_platform_data *pd = NULL;

	pd = lcd->lcd_pd;
	mutex_lock(&lcd->lock);
	if (!lcd->enabled) {
		ret = regulator_bulk_enable(ARRAY_SIZE(supplies), supplies);
		if (ret)
			goto out;

		lcd->enabled = true;
	}
	msleep(pd->power_on_delay);
out:
	mutex_unlock(&lcd->lock);
}