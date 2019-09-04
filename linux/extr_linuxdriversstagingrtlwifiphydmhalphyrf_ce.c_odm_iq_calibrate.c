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
struct phy_dm_struct {scalar_t__* channel; scalar_t__ pre_channel; int linked_interval; int /*<<< orphan*/ * is_scan_in_process; scalar_t__ is_linked; void* adapter; } ;

/* Variables and functions */
 scalar_t__ IS_HARDWARE_TYPE_8812AU (void*) ; 
 scalar_t__ IS_HARDWARE_TYPE_8814A (void*) ; 
 scalar_t__ IS_HARDWARE_TYPE_8822B (void*) ; 
 int /*<<< orphan*/  phy_iq_calibrate_8822b (struct phy_dm_struct*,int) ; 

__attribute__((used)) static void odm_iq_calibrate(struct phy_dm_struct *dm)
{
	void *adapter = dm->adapter;

	if (IS_HARDWARE_TYPE_8812AU(adapter))
		return;

	if (dm->is_linked) {
		if ((*dm->channel != dm->pre_channel) &&
		    (!*dm->is_scan_in_process)) {
			dm->pre_channel = *dm->channel;
			dm->linked_interval = 0;
		}

		if (dm->linked_interval < 3)
			dm->linked_interval++;

		if (dm->linked_interval == 2) {
			if (IS_HARDWARE_TYPE_8814A(adapter))
				;

			else if (IS_HARDWARE_TYPE_8822B(adapter))
				phy_iq_calibrate_8822b(dm, false);
		}
	} else {
		dm->linked_interval = 0;
	}
}