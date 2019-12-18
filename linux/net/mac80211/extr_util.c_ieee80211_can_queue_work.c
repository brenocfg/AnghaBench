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
struct ieee80211_local {int /*<<< orphan*/  resuming; scalar_t__ suspended; scalar_t__ quiescing; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static bool ieee80211_can_queue_work(struct ieee80211_local *local)
{
	if (local->quiescing || (local->suspended && !local->resuming)) {
		pr_warn("queueing ieee80211 work while going to suspend\n");
		return false;
	}

	return true;
}