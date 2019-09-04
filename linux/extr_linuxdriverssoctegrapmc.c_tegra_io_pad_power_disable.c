#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  enum tegra_io_pad { ____Placeholder_tegra_io_pad } tegra_io_pad ;
struct TYPE_2__ {int /*<<< orphan*/  powergates_lock; } ;

/* Variables and functions */
 int IO_DPD_REQ_CODE_ON ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* pmc ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int tegra_io_pad_poll (unsigned long,int,int,int) ; 
 int tegra_io_pad_prepare (int,unsigned long*,unsigned long*,int*) ; 
 int /*<<< orphan*/  tegra_io_pad_unprepare () ; 
 int /*<<< orphan*/  tegra_pmc_writel (int,unsigned long) ; 

int tegra_io_pad_power_disable(enum tegra_io_pad id)
{
	unsigned long request, status;
	u32 mask;
	int err;

	mutex_lock(&pmc->powergates_lock);

	err = tegra_io_pad_prepare(id, &request, &status, &mask);
	if (err < 0) {
		pr_err("failed to prepare I/O pad: %d\n", err);
		goto unlock;
	}

	tegra_pmc_writel(IO_DPD_REQ_CODE_ON | mask, request);

	err = tegra_io_pad_poll(status, mask, mask, 250);
	if (err < 0) {
		pr_err("failed to disable I/O pad: %d\n", err);
		goto unlock;
	}

	tegra_io_pad_unprepare();

unlock:
	mutex_unlock(&pmc->powergates_lock);
	return err;
}