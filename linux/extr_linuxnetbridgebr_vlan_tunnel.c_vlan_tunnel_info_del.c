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
struct net_bridge_vlan_group {int /*<<< orphan*/  tunnel_hash; } ;
struct TYPE_4__ {TYPE_1__* tunnel_dst; scalar_t__ tunnel_id; } ;
struct net_bridge_vlan {TYPE_2__ tinfo; int /*<<< orphan*/  tnode; } ;
struct TYPE_3__ {int /*<<< orphan*/  dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  br_vlan_tunnel_rht_params ; 
 int /*<<< orphan*/  dst_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void vlan_tunnel_info_del(struct net_bridge_vlan_group *vg,
			  struct net_bridge_vlan *vlan)
{
	if (!vlan->tinfo.tunnel_dst)
		return;
	rhashtable_remove_fast(&vg->tunnel_hash, &vlan->tnode,
			       br_vlan_tunnel_rht_params);
	vlan->tinfo.tunnel_id = 0;
	dst_release(&vlan->tinfo.tunnel_dst->dst);
	vlan->tinfo.tunnel_dst = NULL;
}