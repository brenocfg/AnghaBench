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
struct netdevsim {int num_vfs; TYPE_1__* vfconfigs; } ;
struct net_device {int dummy; } ;
struct ifla_vf_info {int vf; int /*<<< orphan*/  rss_query_en; int /*<<< orphan*/  trusted; int /*<<< orphan*/  spoofchk; int /*<<< orphan*/  mac; int /*<<< orphan*/  qos; int /*<<< orphan*/  vlan_proto; int /*<<< orphan*/  vlan; int /*<<< orphan*/  max_tx_rate; int /*<<< orphan*/  min_tx_rate; int /*<<< orphan*/  linkstate; } ;
struct TYPE_2__ {int /*<<< orphan*/  rss_query_enabled; int /*<<< orphan*/  trusted; int /*<<< orphan*/  spoofchk_enabled; int /*<<< orphan*/  vf_mac; int /*<<< orphan*/  qos; int /*<<< orphan*/  vlan_proto; int /*<<< orphan*/  vlan; int /*<<< orphan*/  max_tx_rate; int /*<<< orphan*/  min_tx_rate; int /*<<< orphan*/  link_state; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct netdevsim* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
nsim_get_vf_config(struct net_device *dev, int vf, struct ifla_vf_info *ivi)
{
	struct netdevsim *ns = netdev_priv(dev);

	if (vf >= ns->num_vfs)
		return -EINVAL;

	ivi->vf = vf;
	ivi->linkstate = ns->vfconfigs[vf].link_state;
	ivi->min_tx_rate = ns->vfconfigs[vf].min_tx_rate;
	ivi->max_tx_rate = ns->vfconfigs[vf].max_tx_rate;
	ivi->vlan = ns->vfconfigs[vf].vlan;
	ivi->vlan_proto = ns->vfconfigs[vf].vlan_proto;
	ivi->qos = ns->vfconfigs[vf].qos;
	memcpy(&ivi->mac, ns->vfconfigs[vf].vf_mac, ETH_ALEN);
	ivi->spoofchk = ns->vfconfigs[vf].spoofchk_enabled;
	ivi->trusted = ns->vfconfigs[vf].trusted;
	ivi->rss_query_en = ns->vfconfigs[vf].rss_query_enabled;

	return 0;
}