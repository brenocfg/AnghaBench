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
struct qtnf_wmac {int dummy; } ;
struct TYPE_2__ {scalar_t__ iftype; int /*<<< orphan*/  wiphy; } ;
struct qtnf_vif {int sta_state; TYPE_1__ wdev; int /*<<< orphan*/  netdev; int /*<<< orphan*/  bssid; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
#define  QTNF_STA_CONNECTED 130 
#define  QTNF_STA_CONNECTING 129 
#define  QTNF_STA_DISCONNECTED 128 
 int /*<<< orphan*/  WLAN_REASON_DEAUTH_LEAVING ; 
 int /*<<< orphan*/  WLAN_STATUS_UNSPECIFIED_FAILURE ; 
 int /*<<< orphan*/  cfg80211_connect_result (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_disconnected (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtnf_disconnect (int /*<<< orphan*/ ,struct net_device*,int /*<<< orphan*/ ) ; 
 struct qtnf_vif* qtnf_netdev_get_priv (struct net_device*) ; 
 int /*<<< orphan*/  qtnf_scan_done (struct qtnf_wmac*,int) ; 
 struct qtnf_wmac* wiphy_priv (int /*<<< orphan*/ ) ; 

void qtnf_virtual_intf_cleanup(struct net_device *ndev)
{
	struct qtnf_vif *vif = qtnf_netdev_get_priv(ndev);
	struct qtnf_wmac *mac = wiphy_priv(vif->wdev.wiphy);

	if (vif->wdev.iftype == NL80211_IFTYPE_STATION) {
		switch (vif->sta_state) {
		case QTNF_STA_DISCONNECTED:
			break;
		case QTNF_STA_CONNECTING:
			cfg80211_connect_result(vif->netdev,
						vif->bssid, NULL, 0,
						NULL, 0,
						WLAN_STATUS_UNSPECIFIED_FAILURE,
						GFP_KERNEL);
			qtnf_disconnect(vif->wdev.wiphy, ndev,
					WLAN_REASON_DEAUTH_LEAVING);
			break;
		case QTNF_STA_CONNECTED:
			cfg80211_disconnected(vif->netdev,
					      WLAN_REASON_DEAUTH_LEAVING,
					      NULL, 0, 1, GFP_KERNEL);
			qtnf_disconnect(vif->wdev.wiphy, ndev,
					WLAN_REASON_DEAUTH_LEAVING);
			break;
		}

		vif->sta_state = QTNF_STA_DISCONNECTED;
	}

	qtnf_scan_done(mac, true);
}