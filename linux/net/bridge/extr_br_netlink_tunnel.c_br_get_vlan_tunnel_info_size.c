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
struct net_bridge_vlan_group {int dummy; } ;

/* Variables and functions */
 int __get_num_vlan_tunnel_infos (struct net_bridge_vlan_group*) ; 
 int __get_vlan_tinfo_size () ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

int br_get_vlan_tunnel_info_size(struct net_bridge_vlan_group *vg)
{
	int num_tinfos;

	if (!vg)
		return 0;

	rcu_read_lock();
	num_tinfos = __get_num_vlan_tunnel_infos(vg);
	rcu_read_unlock();

	return num_tinfos * __get_vlan_tinfo_size();
}