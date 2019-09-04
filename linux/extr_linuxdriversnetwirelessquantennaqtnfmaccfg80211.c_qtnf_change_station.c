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
struct wiphy {int dummy; } ;
struct station_parameters {int dummy; } ;
struct qtnf_vif {int /*<<< orphan*/  vifid; TYPE_1__* mac; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  macid; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int qtnf_cmd_send_change_sta (struct qtnf_vif*,int /*<<< orphan*/  const*,struct station_parameters*) ; 
 struct qtnf_vif* qtnf_netdev_get_priv (struct net_device*) ; 

__attribute__((used)) static int
qtnf_change_station(struct wiphy *wiphy, struct net_device *dev,
		    const u8 *mac, struct station_parameters *params)
{
	struct qtnf_vif *vif = qtnf_netdev_get_priv(dev);
	int ret;

	ret = qtnf_cmd_send_change_sta(vif, mac, params);
	if (ret)
		pr_err("VIF%u.%u: failed to change STA %pM\n",
		       vif->mac->macid, vif->vifid, mac);

	return ret;
}