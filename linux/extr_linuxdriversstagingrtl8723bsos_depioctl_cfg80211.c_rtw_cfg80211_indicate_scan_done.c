#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rtw_wdev_priv {int /*<<< orphan*/  scan_req_lock; TYPE_2__* scan_request; TYPE_1__* rtw_wdev; } ;
struct cfg80211_scan_info {int aborted; } ;
struct adapter {int dummy; } ;
struct TYPE_4__ {scalar_t__ wiphy; } ;
struct TYPE_3__ {scalar_t__ wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_8192C (char*) ; 
 struct rtw_wdev_priv* adapter_wdev_data (struct adapter*) ; 
 int /*<<< orphan*/  cfg80211_scan_done (TYPE_2__*,struct cfg80211_scan_info*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void rtw_cfg80211_indicate_scan_done(struct adapter *adapter, bool aborted)
{
	struct rtw_wdev_priv *pwdev_priv = adapter_wdev_data(adapter);
	struct cfg80211_scan_info info = {
		.aborted = aborted
	};

	spin_lock_bh(&pwdev_priv->scan_req_lock);
	if (pwdev_priv->scan_request != NULL) {
		#ifdef DEBUG_CFG80211
		DBG_871X("%s with scan req\n", __func__);
		#endif

		/* avoid WARN_ON(request != wiphy_to_dev(request->wiphy)->scan_req); */
		if (pwdev_priv->scan_request->wiphy != pwdev_priv->rtw_wdev->wiphy)
		{
			DBG_8192C("error wiphy compare\n");
		}
		else
		{
			cfg80211_scan_done(pwdev_priv->scan_request, &info);
		}

		pwdev_priv->scan_request = NULL;
	} else {
		#ifdef DEBUG_CFG80211
		DBG_871X("%s without scan req\n", __func__);
		#endif
	}
	spin_unlock_bh(&pwdev_priv->scan_req_lock);
}