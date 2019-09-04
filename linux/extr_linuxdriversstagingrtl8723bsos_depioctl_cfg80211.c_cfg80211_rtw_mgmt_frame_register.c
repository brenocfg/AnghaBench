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
typedef  int u16 ;
struct wireless_dev {int dummy; } ;
struct wiphy {int dummy; } ;
struct net_device {int dummy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int IEEE80211_FTYPE_MGMT ; 
 int IEEE80211_STYPE_PROBE_REQ ; 
 scalar_t__ rtw_netdev_priv (struct net_device*) ; 
 struct net_device* wdev_to_ndev (struct wireless_dev*) ; 

__attribute__((used)) static void cfg80211_rtw_mgmt_frame_register(struct wiphy *wiphy,
	struct wireless_dev *wdev,
	u16 frame_type, bool reg)
{
	struct net_device *ndev = wdev_to_ndev(wdev);
	struct adapter *adapter;

	if (ndev == NULL)
		goto exit;

	adapter = (struct adapter *)rtw_netdev_priv(ndev);

#ifdef DEBUG_CFG80211
	DBG_871X(FUNC_ADPT_FMT" frame_type:%x, reg:%d\n", FUNC_ADPT_ARG(adapter),
		frame_type, reg);
#endif

	if (frame_type != (IEEE80211_FTYPE_MGMT | IEEE80211_STYPE_PROBE_REQ))
		return;
exit:
	return;
}