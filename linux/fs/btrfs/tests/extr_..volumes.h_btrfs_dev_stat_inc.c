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
struct btrfs_device {int /*<<< orphan*/  dev_stats_ccnt; int /*<<< orphan*/ * dev_stat_values; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 

__attribute__((used)) static inline void btrfs_dev_stat_inc(struct btrfs_device *dev,
				      int index)
{
	atomic_inc(dev->dev_stat_values + index);
	/*
	 * This memory barrier orders stores updating statistics before stores
	 * updating dev_stats_ccnt.
	 *
	 * It pairs with smp_rmb() in btrfs_run_dev_stats().
	 */
	smp_mb__before_atomic();
	atomic_inc(&dev->dev_stats_ccnt);
}