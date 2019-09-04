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
typedef  int /*<<< orphan*/  u64 ;
struct wiphy {int dummy; } ;
struct wil6210_vif {scalar_t__ mid; } ;
struct wil6210_priv {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct wil6210_vif* ndev_to_vif (struct net_device*) ; 
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*,int) ; 
 struct wil6210_priv* wiphy_to_wil (struct wiphy*) ; 
 int wmi_stop_sched_scan (struct wil6210_priv*) ; 

__attribute__((used)) static int
wil_cfg80211_sched_scan_stop(struct wiphy *wiphy, struct net_device *dev,
			     u64 reqid)
{
	struct wil6210_priv *wil = wiphy_to_wil(wiphy);
	struct wil6210_vif *vif = ndev_to_vif(dev);
	int rc;

	if (vif->mid != 0)
		return -EOPNOTSUPP;

	rc = wmi_stop_sched_scan(wil);
	/* device would return error if it thinks PNO is already stopped.
	 * ignore the return code so user space and driver gets back in-sync
	 */
	wil_dbg_misc(wil, "sched scan stopped (%d)\n", rc);

	return 0;
}