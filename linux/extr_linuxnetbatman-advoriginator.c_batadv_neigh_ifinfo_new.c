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
struct batadv_neigh_node {int /*<<< orphan*/  ifinfo_lock; int /*<<< orphan*/  ifinfo_list; } ;
struct batadv_neigh_ifinfo {int /*<<< orphan*/  list; int /*<<< orphan*/  refcount; struct batadv_hard_iface* if_outgoing; } ;
struct batadv_hard_iface {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 struct batadv_neigh_ifinfo* batadv_neigh_ifinfo_get (struct batadv_neigh_node*,struct batadv_hard_iface*) ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct batadv_neigh_ifinfo* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

struct batadv_neigh_ifinfo *
batadv_neigh_ifinfo_new(struct batadv_neigh_node *neigh,
			struct batadv_hard_iface *if_outgoing)
{
	struct batadv_neigh_ifinfo *neigh_ifinfo;

	spin_lock_bh(&neigh->ifinfo_lock);

	neigh_ifinfo = batadv_neigh_ifinfo_get(neigh, if_outgoing);
	if (neigh_ifinfo)
		goto out;

	neigh_ifinfo = kzalloc(sizeof(*neigh_ifinfo), GFP_ATOMIC);
	if (!neigh_ifinfo)
		goto out;

	if (if_outgoing)
		kref_get(&if_outgoing->refcount);

	INIT_HLIST_NODE(&neigh_ifinfo->list);
	kref_init(&neigh_ifinfo->refcount);
	neigh_ifinfo->if_outgoing = if_outgoing;

	kref_get(&neigh_ifinfo->refcount);
	hlist_add_head_rcu(&neigh_ifinfo->list, &neigh->ifinfo_list);

out:
	spin_unlock_bh(&neigh->ifinfo_lock);

	return neigh_ifinfo;
}