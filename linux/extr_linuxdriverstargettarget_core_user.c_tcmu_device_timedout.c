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
struct tcmu_dev {int /*<<< orphan*/  timedout_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcmu_unmap_work ; 
 int /*<<< orphan*/  timed_out_udevs ; 
 int /*<<< orphan*/  timed_out_udevs_lock ; 

__attribute__((used)) static void tcmu_device_timedout(struct tcmu_dev *udev)
{
	spin_lock(&timed_out_udevs_lock);
	if (list_empty(&udev->timedout_entry))
		list_add_tail(&udev->timedout_entry, &timed_out_udevs);
	spin_unlock(&timed_out_udevs_lock);

	schedule_delayed_work(&tcmu_unmap_work, 0);
}