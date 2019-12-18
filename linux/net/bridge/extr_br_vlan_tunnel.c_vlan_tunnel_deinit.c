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
struct net_bridge_vlan_group {int /*<<< orphan*/  tunnel_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  rhashtable_destroy (int /*<<< orphan*/ *) ; 

void vlan_tunnel_deinit(struct net_bridge_vlan_group *vg)
{
	rhashtable_destroy(&vg->tunnel_hash);
}