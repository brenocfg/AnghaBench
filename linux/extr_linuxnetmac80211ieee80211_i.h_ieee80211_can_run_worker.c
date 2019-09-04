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
struct ieee80211_local {scalar_t__ suspended; scalar_t__ quiescing; } ;

/* Variables and functions */

__attribute__((used)) static inline bool ieee80211_can_run_worker(struct ieee80211_local *local)
{
	/*
	 * If quiescing is set, we are racing with __ieee80211_suspend.
	 * __ieee80211_suspend flushes the workers after setting quiescing,
	 * and we check quiescing / suspended before enqueing new workers.
	 * We should abort the worker to avoid the races below.
	 */
	if (local->quiescing)
		return false;

	/*
	 * We might already be suspended if the following scenario occurs:
	 * __ieee80211_suspend		Control path
	 *
	 *				if (local->quiescing)
	 *					return;
	 * local->quiescing = true;
	 * flush_workqueue();
	 *				queue_work(...);
	 * local->suspended = true;
	 * local->quiescing = false;
	 *				worker starts running...
	 */
	if (local->suspended)
		return false;

	return true;
}