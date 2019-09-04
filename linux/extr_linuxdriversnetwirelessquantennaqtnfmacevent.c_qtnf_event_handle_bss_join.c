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
typedef  int u16 ;
struct TYPE_3__ {scalar_t__ iftype; } ;
struct qtnf_vif {scalar_t__ sta_state; int /*<<< orphan*/  netdev; int /*<<< orphan*/  vifid; TYPE_2__* mac; TYPE_1__ wdev; } ;
struct qlink_event_bss_join {int /*<<< orphan*/  status; int /*<<< orphan*/  bssid; } ;
struct TYPE_4__ {int /*<<< orphan*/  macid; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPROTO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 scalar_t__ QTNF_STA_CONNECTED ; 
 scalar_t__ QTNF_STA_CONNECTING ; 
 scalar_t__ QTNF_STA_DISCONNECTED ; 
 scalar_t__ WLAN_STATUS_SUCCESS ; 
 int /*<<< orphan*/  cfg80211_connect_result (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
qtnf_event_handle_bss_join(struct qtnf_vif *vif,
			   const struct qlink_event_bss_join *join_info,
			   u16 len)
{
	if (unlikely(len < sizeof(*join_info))) {
		pr_err("VIF%u.%u: payload is too short (%u < %zu)\n",
		       vif->mac->macid, vif->vifid, len,
		       sizeof(struct qlink_event_bss_join));
		return -EINVAL;
	}

	if (vif->wdev.iftype != NL80211_IFTYPE_STATION) {
		pr_err("VIF%u.%u: BSS_JOIN event when not in STA mode\n",
		       vif->mac->macid, vif->vifid);
		return -EPROTO;
	}

	if (vif->sta_state != QTNF_STA_CONNECTING) {
		pr_err("VIF%u.%u: BSS_JOIN event when STA is not connecting\n",
		       vif->mac->macid, vif->vifid);
		return -EPROTO;
	}

	pr_debug("VIF%u.%u: BSSID:%pM\n", vif->mac->macid, vif->vifid,
		 join_info->bssid);

	cfg80211_connect_result(vif->netdev, join_info->bssid, NULL, 0, NULL,
				0, le16_to_cpu(join_info->status), GFP_KERNEL);

	if (le16_to_cpu(join_info->status) == WLAN_STATUS_SUCCESS) {
		vif->sta_state = QTNF_STA_CONNECTED;
		netif_carrier_on(vif->netdev);
	} else {
		vif->sta_state = QTNF_STA_DISCONNECTED;
	}

	return 0;
}