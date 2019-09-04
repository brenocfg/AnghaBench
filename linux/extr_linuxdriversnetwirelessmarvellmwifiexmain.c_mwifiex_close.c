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
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;
struct mwifiex_private {int scan_aborting; TYPE_1__ wdev; int /*<<< orphan*/  adapter; scalar_t__ sched_scanning; int /*<<< orphan*/ * scan_request; } ;
struct cfg80211_scan_info {int aborted; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  cfg80211_scan_done (int /*<<< orphan*/ *,struct cfg80211_scan_info*) ; 
 int /*<<< orphan*/  cfg80211_sched_scan_stopped (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct mwifiex_private* mwifiex_netdev_get_priv (struct net_device*) ; 
 int /*<<< orphan*/  mwifiex_stop_bg_scan (struct mwifiex_private*) ; 

__attribute__((used)) static int
mwifiex_close(struct net_device *dev)
{
	struct mwifiex_private *priv = mwifiex_netdev_get_priv(dev);

	if (priv->scan_request) {
		struct cfg80211_scan_info info = {
			.aborted = true,
		};

		mwifiex_dbg(priv->adapter, INFO,
			    "aborting scan on ndo_stop\n");
		cfg80211_scan_done(priv->scan_request, &info);
		priv->scan_request = NULL;
		priv->scan_aborting = true;
	}

	if (priv->sched_scanning) {
		mwifiex_dbg(priv->adapter, INFO,
			    "aborting bgscan on ndo_stop\n");
		mwifiex_stop_bg_scan(priv);
		cfg80211_sched_scan_stopped(priv->wdev.wiphy, 0);
	}

	return 0;
}