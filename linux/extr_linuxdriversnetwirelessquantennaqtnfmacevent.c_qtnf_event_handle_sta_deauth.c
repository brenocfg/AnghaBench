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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct qtnf_wmac {int /*<<< orphan*/  macid; } ;
struct TYPE_2__ {scalar_t__ iftype; } ;
struct qtnf_vif {int /*<<< orphan*/  netdev; int /*<<< orphan*/  vifid; TYPE_1__ wdev; } ;
struct qlink_event_sta_deauth {int /*<<< orphan*/ * sta_addr; int /*<<< orphan*/  reason; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPROTO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  cfg80211_del_sta (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ qtnf_sta_list_del (struct qtnf_vif*,int /*<<< orphan*/  const*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
qtnf_event_handle_sta_deauth(struct qtnf_wmac *mac, struct qtnf_vif *vif,
			     const struct qlink_event_sta_deauth *sta_deauth,
			     u16 len)
{
	const u8 *sta_addr;
	u16 reason;

	if (unlikely(len < sizeof(*sta_deauth))) {
		pr_err("VIF%u.%u: payload is too short (%u < %zu)\n",
		       mac->macid, vif->vifid, len,
		       sizeof(struct qlink_event_sta_deauth));
		return -EINVAL;
	}

	if (vif->wdev.iftype != NL80211_IFTYPE_AP) {
		pr_err("VIF%u.%u: STA_DEAUTH event when not in AP mode\n",
		       mac->macid, vif->vifid);
		return -EPROTO;
	}

	sta_addr = sta_deauth->sta_addr;
	reason = le16_to_cpu(sta_deauth->reason);

	pr_debug("VIF%u.%u: MAC:%pM reason:%x\n", mac->macid, vif->vifid,
		 sta_addr, reason);

	if (qtnf_sta_list_del(vif, sta_addr))
		cfg80211_del_sta(vif->netdev, sta_deauth->sta_addr,
				 GFP_KERNEL);

	return 0;
}