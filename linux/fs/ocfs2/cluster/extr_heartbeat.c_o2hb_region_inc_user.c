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

/* Variables and functions */
 scalar_t__ O2HB_PIN_CUT_OFF ; 
 int /*<<< orphan*/  O2NM_MAX_REGIONS ; 
 scalar_t__ bitmap_weight (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int o2hb_dependent_users ; 
 int /*<<< orphan*/  o2hb_global_heartbeat_active () ; 
 int /*<<< orphan*/  o2hb_live_lock ; 
 int /*<<< orphan*/  o2hb_quorum_region_bitmap ; 
 int o2hb_region_pin (char const*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int o2hb_region_inc_user(const char *region_uuid)
{
	int ret = 0;

	spin_lock(&o2hb_live_lock);

	/* local heartbeat */
	if (!o2hb_global_heartbeat_active()) {
	    ret = o2hb_region_pin(region_uuid);
	    goto unlock;
	}

	/*
	 * if global heartbeat active and this is the first dependent user,
	 * pin all regions if quorum region count <= CUT_OFF
	 */
	o2hb_dependent_users++;
	if (o2hb_dependent_users > 1)
		goto unlock;

	if (bitmap_weight(o2hb_quorum_region_bitmap,
			   O2NM_MAX_REGIONS) <= O2HB_PIN_CUT_OFF)
		ret = o2hb_region_pin(NULL);

unlock:
	spin_unlock(&o2hb_live_lock);
	return ret;
}