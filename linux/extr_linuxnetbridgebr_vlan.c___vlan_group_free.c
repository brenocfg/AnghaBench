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
struct net_bridge_vlan_group {int /*<<< orphan*/  vlan_hash; int /*<<< orphan*/  vlan_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct net_bridge_vlan_group*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rhashtable_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlan_tunnel_deinit (struct net_bridge_vlan_group*) ; 

__attribute__((used)) static void __vlan_group_free(struct net_bridge_vlan_group *vg)
{
	WARN_ON(!list_empty(&vg->vlan_list));
	rhashtable_destroy(&vg->vlan_hash);
	vlan_tunnel_deinit(vg);
	kfree(vg);
}