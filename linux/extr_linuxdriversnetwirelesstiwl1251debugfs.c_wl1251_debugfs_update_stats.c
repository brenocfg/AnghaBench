#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ fw_stats_update; int /*<<< orphan*/  fw_stats; } ;
struct wl1251 {scalar_t__ state; int /*<<< orphan*/  mutex; TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  WL1251_DEBUGFS_STATS_LIFETIME ; 
 scalar_t__ WL1251_STATE_ON ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  wl1251_acx_statistics (struct wl1251*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1251_ps_elp_sleep (struct wl1251*) ; 
 int wl1251_ps_elp_wakeup (struct wl1251*) ; 

__attribute__((used)) static void wl1251_debugfs_update_stats(struct wl1251 *wl)
{
	int ret;

	mutex_lock(&wl->mutex);

	ret = wl1251_ps_elp_wakeup(wl);
	if (ret < 0)
		goto out;

	if (wl->state == WL1251_STATE_ON &&
	    time_after(jiffies, wl->stats.fw_stats_update +
		       msecs_to_jiffies(WL1251_DEBUGFS_STATS_LIFETIME))) {
		wl1251_acx_statistics(wl, wl->stats.fw_stats);
		wl->stats.fw_stats_update = jiffies;
	}

	wl1251_ps_elp_sleep(wl);

out:
	mutex_unlock(&wl->mutex);
}