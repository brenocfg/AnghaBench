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
struct o2hb_region {int /*<<< orphan*/  hr_nego_node_bitmap; int /*<<< orphan*/  hr_nego_timeout_work; int /*<<< orphan*/  hr_write_timeout_work; int /*<<< orphan*/  hr_region_num; int /*<<< orphan*/  hr_steady_iterations; } ;

/* Variables and functions */
 int /*<<< orphan*/  ML_HEARTBEAT ; 
 int /*<<< orphan*/  O2HB_MAX_WRITE_TIMEOUT_MS ; 
 int /*<<< orphan*/  O2HB_NEGO_TIMEOUT_MS ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  o2hb_failed_region_bitmap ; 
 scalar_t__ o2hb_global_heartbeat_active () ; 
 int /*<<< orphan*/  o2hb_live_lock ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void o2hb_arm_timeout(struct o2hb_region *reg)
{
	/* Arm writeout only after thread reaches steady state */
	if (atomic_read(&reg->hr_steady_iterations) != 0)
		return;

	mlog(ML_HEARTBEAT, "Queue write timeout for %u ms\n",
	     O2HB_MAX_WRITE_TIMEOUT_MS);

	if (o2hb_global_heartbeat_active()) {
		spin_lock(&o2hb_live_lock);
		clear_bit(reg->hr_region_num, o2hb_failed_region_bitmap);
		spin_unlock(&o2hb_live_lock);
	}
	cancel_delayed_work(&reg->hr_write_timeout_work);
	schedule_delayed_work(&reg->hr_write_timeout_work,
			      msecs_to_jiffies(O2HB_MAX_WRITE_TIMEOUT_MS));

	cancel_delayed_work(&reg->hr_nego_timeout_work);
	/* negotiate timeout must be less than write timeout. */
	schedule_delayed_work(&reg->hr_nego_timeout_work,
			      msecs_to_jiffies(O2HB_NEGO_TIMEOUT_MS));
	memset(reg->hr_nego_node_bitmap, 0, sizeof(reg->hr_nego_node_bitmap));
}