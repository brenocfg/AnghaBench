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
struct batadv_orig_node_vlan {unsigned short vid; int /*<<< orphan*/  list; int /*<<< orphan*/  refcount; } ;
struct batadv_orig_node {int /*<<< orphan*/  vlan_list_lock; int /*<<< orphan*/  vlan_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct batadv_orig_node_vlan* batadv_orig_node_vlan_get (struct batadv_orig_node*,unsigned short) ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct batadv_orig_node_vlan* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

struct batadv_orig_node_vlan *
batadv_orig_node_vlan_new(struct batadv_orig_node *orig_node,
			  unsigned short vid)
{
	struct batadv_orig_node_vlan *vlan;

	spin_lock_bh(&orig_node->vlan_list_lock);

	/* first look if an object for this vid already exists */
	vlan = batadv_orig_node_vlan_get(orig_node, vid);
	if (vlan)
		goto out;

	vlan = kzalloc(sizeof(*vlan), GFP_ATOMIC);
	if (!vlan)
		goto out;

	kref_init(&vlan->refcount);
	vlan->vid = vid;

	kref_get(&vlan->refcount);
	hlist_add_head_rcu(&vlan->list, &orig_node->vlan_list);

out:
	spin_unlock_bh(&orig_node->vlan_list_lock);

	return vlan;
}