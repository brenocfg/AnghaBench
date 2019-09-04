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
struct TYPE_2__ {int /*<<< orphan*/  num_entries; } ;
struct batadv_orig_node_vlan {int /*<<< orphan*/  list; TYPE_1__ tt; } ;
struct batadv_orig_node {int /*<<< orphan*/  vlan_list_lock; } ;

/* Variables and functions */
 scalar_t__ atomic_add_return (int,int /*<<< orphan*/ *) ; 
 struct batadv_orig_node_vlan* batadv_orig_node_vlan_new (struct batadv_orig_node*,unsigned short) ; 
 int /*<<< orphan*/  batadv_orig_node_vlan_put (struct batadv_orig_node_vlan*) ; 
 int /*<<< orphan*/  hlist_del_init_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_unhashed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void batadv_tt_global_size_mod(struct batadv_orig_node *orig_node,
				      unsigned short vid, int v)
{
	struct batadv_orig_node_vlan *vlan;

	vlan = batadv_orig_node_vlan_new(orig_node, vid);
	if (!vlan)
		return;

	if (atomic_add_return(v, &vlan->tt.num_entries) == 0) {
		spin_lock_bh(&orig_node->vlan_list_lock);
		if (!hlist_unhashed(&vlan->list)) {
			hlist_del_init_rcu(&vlan->list);
			batadv_orig_node_vlan_put(vlan);
		}
		spin_unlock_bh(&orig_node->vlan_list_lock);
	}

	batadv_orig_node_vlan_put(vlan);
}