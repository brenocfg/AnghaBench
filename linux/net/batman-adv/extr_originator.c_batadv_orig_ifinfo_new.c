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
struct batadv_orig_node {int /*<<< orphan*/  neigh_list_lock; int /*<<< orphan*/  ifinfo_list; } ;
struct batadv_orig_ifinfo {unsigned long batman_seqno_reset; int /*<<< orphan*/  list; int /*<<< orphan*/  refcount; struct batadv_hard_iface* if_outgoing; } ;
struct batadv_hard_iface {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 struct batadv_hard_iface* BATADV_IF_DEFAULT ; 
 int /*<<< orphan*/  BATADV_RESET_PROTECTION_MS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 struct batadv_orig_ifinfo* batadv_orig_ifinfo_get (struct batadv_orig_node*,struct batadv_hard_iface*) ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int jiffies ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct batadv_orig_ifinfo* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

struct batadv_orig_ifinfo *
batadv_orig_ifinfo_new(struct batadv_orig_node *orig_node,
		       struct batadv_hard_iface *if_outgoing)
{
	struct batadv_orig_ifinfo *orig_ifinfo;
	unsigned long reset_time;

	spin_lock_bh(&orig_node->neigh_list_lock);

	orig_ifinfo = batadv_orig_ifinfo_get(orig_node, if_outgoing);
	if (orig_ifinfo)
		goto out;

	orig_ifinfo = kzalloc(sizeof(*orig_ifinfo), GFP_ATOMIC);
	if (!orig_ifinfo)
		goto out;

	if (if_outgoing != BATADV_IF_DEFAULT)
		kref_get(&if_outgoing->refcount);

	reset_time = jiffies - 1;
	reset_time -= msecs_to_jiffies(BATADV_RESET_PROTECTION_MS);
	orig_ifinfo->batman_seqno_reset = reset_time;
	orig_ifinfo->if_outgoing = if_outgoing;
	INIT_HLIST_NODE(&orig_ifinfo->list);
	kref_init(&orig_ifinfo->refcount);

	kref_get(&orig_ifinfo->refcount);
	hlist_add_head_rcu(&orig_ifinfo->list,
			   &orig_node->ifinfo_list);
out:
	spin_unlock_bh(&orig_node->neigh_list_lock);
	return orig_ifinfo;
}