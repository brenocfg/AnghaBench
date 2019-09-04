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
struct fusb302_chip {int /*<<< orphan*/  dev; int /*<<< orphan*/  pm_suspend; } ;

/* Variables and functions */
 int FUSB302_RESUME_RETRY ; 
 int /*<<< orphan*/  FUSB302_RESUME_RETRY_SLEEP ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool fusb302_is_suspended(struct fusb302_chip *chip)
{
	int retry_cnt;

	for (retry_cnt = 0; retry_cnt < FUSB302_RESUME_RETRY; retry_cnt++) {
		if (atomic_read(&chip->pm_suspend)) {
			dev_err(chip->dev, "i2c: pm suspend, retry %d/%d\n",
				retry_cnt + 1, FUSB302_RESUME_RETRY);
			msleep(FUSB302_RESUME_RETRY_SLEEP);
		} else {
			return false;
		}
	}

	return true;
}