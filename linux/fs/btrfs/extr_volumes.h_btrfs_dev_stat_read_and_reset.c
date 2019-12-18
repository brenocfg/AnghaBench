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
struct btrfs_device {int /*<<< orphan*/  dev_stats_ccnt; scalar_t__ dev_stat_values; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_xchg (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int btrfs_dev_stat_read_and_reset(struct btrfs_device *dev,
						int index)
{
	int ret;

	ret = atomic_xchg(dev->dev_stat_values + index, 0);
	/*
	 * atomic_xchg implies a full memory barriers as per atomic_t.txt:
	 * - RMW operations that have a return value are fully ordered;
	 *
	 * This implicit memory barriers is paired with the smp_rmb in
	 * btrfs_run_dev_stats
	 */
	atomic_inc(&dev->dev_stats_ccnt);
	return ret;
}