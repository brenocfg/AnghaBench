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
struct TYPE_2__ {int /*<<< orphan*/  chan; } ;
struct wireless_dev {int cac_started; unsigned long cac_start_time; int /*<<< orphan*/  cac_time_ms; TYPE_1__ chandef; struct wiphy* wiphy; } ;
struct wiphy {int dummy; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  propagate_cac_done_wk; int /*<<< orphan*/  cac_done_chandef; } ;
struct cfg80211_chan_def {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  enum nl80211_radar_event { ____Placeholder_nl80211_radar_event } nl80211_radar_event ;

/* Variables and functions */
 int /*<<< orphan*/  NL80211_DFS_AVAILABLE ; 
#define  NL80211_RADAR_CAC_ABORTED 130 
#define  NL80211_RADAR_CAC_FINISHED 129 
#define  NL80211_RADAR_CAC_STARTED 128 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cfg80211_sched_dfs_chan_update (struct cfg80211_registered_device*) ; 
 int /*<<< orphan*/  cfg80211_set_dfs_state (struct wiphy*,struct cfg80211_chan_def const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_wq ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct cfg80211_chan_def const*,int) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nl80211_radar_notify (struct cfg80211_registered_device*,struct cfg80211_chan_def const*,int,struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time_after_eq (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  trace_cfg80211_cac_event (struct net_device*,int) ; 
 struct cfg80211_registered_device* wiphy_to_rdev (struct wiphy*) ; 

void cfg80211_cac_event(struct net_device *netdev,
			const struct cfg80211_chan_def *chandef,
			enum nl80211_radar_event event, gfp_t gfp)
{
	struct wireless_dev *wdev = netdev->ieee80211_ptr;
	struct wiphy *wiphy = wdev->wiphy;
	struct cfg80211_registered_device *rdev = wiphy_to_rdev(wiphy);
	unsigned long timeout;

	trace_cfg80211_cac_event(netdev, event);

	if (WARN_ON(!wdev->cac_started && event != NL80211_RADAR_CAC_STARTED))
		return;

	if (WARN_ON(!wdev->chandef.chan))
		return;

	switch (event) {
	case NL80211_RADAR_CAC_FINISHED:
		timeout = wdev->cac_start_time +
			  msecs_to_jiffies(wdev->cac_time_ms);
		WARN_ON(!time_after_eq(jiffies, timeout));
		cfg80211_set_dfs_state(wiphy, chandef, NL80211_DFS_AVAILABLE);
		memcpy(&rdev->cac_done_chandef, chandef,
		       sizeof(struct cfg80211_chan_def));
		queue_work(cfg80211_wq, &rdev->propagate_cac_done_wk);
		cfg80211_sched_dfs_chan_update(rdev);
		/* fall through */
	case NL80211_RADAR_CAC_ABORTED:
		wdev->cac_started = false;
		break;
	case NL80211_RADAR_CAC_STARTED:
		wdev->cac_started = true;
		break;
	default:
		WARN_ON(1);
		return;
	}

	nl80211_radar_notify(rdev, chandef, event, netdev, gfp);
}