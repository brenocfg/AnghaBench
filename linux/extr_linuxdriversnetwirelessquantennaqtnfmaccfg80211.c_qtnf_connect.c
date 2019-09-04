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
struct wiphy {int dummy; } ;
struct TYPE_4__ {scalar_t__ iftype; } ;
struct qtnf_vif {scalar_t__ sta_state; int /*<<< orphan*/  vifid; TYPE_1__* mac; int /*<<< orphan*/  bssid; TYPE_2__ wdev; } ;
struct net_device {int dummy; } ;
struct cfg80211_connect_params {int /*<<< orphan*/  bssid; } ;
struct TYPE_3__ {int /*<<< orphan*/  macid; } ;

/* Variables and functions */
 int EBUSY ; 
 int EOPNOTSUPP ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 scalar_t__ QTNF_STA_CONNECTING ; 
 scalar_t__ QTNF_STA_DISCONNECTED ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qtnf_cmd_send_connect (struct qtnf_vif*,struct cfg80211_connect_params*) ; 
 struct qtnf_vif* qtnf_netdev_get_priv (struct net_device*) ; 

__attribute__((used)) static int
qtnf_connect(struct wiphy *wiphy, struct net_device *dev,
	     struct cfg80211_connect_params *sme)
{
	struct qtnf_vif *vif = qtnf_netdev_get_priv(dev);
	int ret;

	if (vif->wdev.iftype != NL80211_IFTYPE_STATION)
		return -EOPNOTSUPP;

	if (vif->sta_state != QTNF_STA_DISCONNECTED)
		return -EBUSY;

	if (sme->bssid)
		ether_addr_copy(vif->bssid, sme->bssid);
	else
		eth_zero_addr(vif->bssid);

	ret = qtnf_cmd_send_connect(vif, sme);
	if (ret) {
		pr_err("VIF%u.%u: failed to connect\n", vif->mac->macid,
		       vif->vifid);
		return ret;
	}

	vif->sta_state = QTNF_STA_CONNECTING;
	return 0;
}