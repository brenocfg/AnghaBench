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
typedef  int u32 ;
struct net_bridge_vlan_group {int num_vlans; } ;

/* Variables and functions */
 int RTEXT_FILTER_BRVLAN ; 
 int __get_num_vlan_infos (struct net_bridge_vlan_group*,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int br_get_num_vlan_infos(struct net_bridge_vlan_group *vg,
				 u32 filter_mask)
{
	int num_vlans;

	if (!vg)
		return 0;

	if (filter_mask & RTEXT_FILTER_BRVLAN)
		return vg->num_vlans;

	rcu_read_lock();
	num_vlans = __get_num_vlan_infos(vg, filter_mask);
	rcu_read_unlock();

	return num_vlans;
}