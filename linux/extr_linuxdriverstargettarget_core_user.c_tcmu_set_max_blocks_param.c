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
typedef  int /*<<< orphan*/  substring_t ;
struct tcmu_dev {int /*<<< orphan*/  cmdr_lock; int /*<<< orphan*/  max_blocks; scalar_t__ data_bitmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TCMU_BLOCKS_TO_MBS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCMU_MBS_TO_BLOCKS (int) ; 
 int match_int (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  tcmu_global_max_blocks ; 

__attribute__((used)) static int tcmu_set_max_blocks_param(struct tcmu_dev *udev, substring_t *arg)
{
	int val, ret;

	ret = match_int(arg, &val);
	if (ret < 0) {
		pr_err("match_int() failed for max_data_area_mb=. Error %d.\n",
		       ret);
		return ret;
	}

	if (val <= 0) {
		pr_err("Invalid max_data_area %d.\n", val);
		return -EINVAL;
	}

	mutex_lock(&udev->cmdr_lock);
	if (udev->data_bitmap) {
		pr_err("Cannot set max_data_area_mb after it has been enabled.\n");
		ret = -EINVAL;
		goto unlock;
	}

	udev->max_blocks = TCMU_MBS_TO_BLOCKS(val);
	if (udev->max_blocks > tcmu_global_max_blocks) {
		pr_err("%d is too large. Adjusting max_data_area_mb to global limit of %u\n",
		       val, TCMU_BLOCKS_TO_MBS(tcmu_global_max_blocks));
		udev->max_blocks = tcmu_global_max_blocks;
	}

unlock:
	mutex_unlock(&udev->cmdr_lock);
	return ret;
}