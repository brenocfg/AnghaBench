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
struct cfg80211_registered_device {int /*<<< orphan*/  dfs_update_channels_wk; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfg80211_wq ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void cfg80211_sched_dfs_chan_update(struct cfg80211_registered_device *rdev)
{
	cancel_delayed_work(&rdev->dfs_update_channels_wk);
	queue_delayed_work(cfg80211_wq, &rdev->dfs_update_channels_wk, 0);
}