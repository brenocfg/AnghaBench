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
struct backing_dev_info {unsigned int max_ratio; scalar_t__ min_ratio; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  bdi_lock ; 
 unsigned int bdi_min_ratio ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int bdi_set_min_ratio(struct backing_dev_info *bdi, unsigned int min_ratio)
{
	int ret = 0;

	spin_lock_bh(&bdi_lock);
	if (min_ratio > bdi->max_ratio) {
		ret = -EINVAL;
	} else {
		min_ratio -= bdi->min_ratio;
		if (bdi_min_ratio + min_ratio < 100) {
			bdi_min_ratio += min_ratio;
			bdi->min_ratio += min_ratio;
		} else {
			ret = -EINVAL;
		}
	}
	spin_unlock_bh(&bdi_lock);

	return ret;
}