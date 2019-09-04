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
 int /*<<< orphan*/  o2hb_dependent_users ; 
 int /*<<< orphan*/  o2hb_global_heartbeat_active () ; 
 int /*<<< orphan*/  o2hb_live_lock ; 
 int /*<<< orphan*/  o2hb_region_unpin (char const*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void o2hb_region_dec_user(const char *region_uuid)
{
	spin_lock(&o2hb_live_lock);

	/* local heartbeat */
	if (!o2hb_global_heartbeat_active()) {
	    o2hb_region_unpin(region_uuid);
	    goto unlock;
	}

	/*
	 * if global heartbeat active and there are no dependent users,
	 * unpin all quorum regions
	 */
	o2hb_dependent_users--;
	if (!o2hb_dependent_users)
		o2hb_region_unpin(NULL);

unlock:
	spin_unlock(&o2hb_live_lock);
}