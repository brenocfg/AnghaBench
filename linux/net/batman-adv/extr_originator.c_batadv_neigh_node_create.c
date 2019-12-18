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
typedef  int /*<<< orphan*/  u8 ;
struct batadv_orig_node {int /*<<< orphan*/  neigh_list_lock; int /*<<< orphan*/  orig; int /*<<< orphan*/  bat_priv; int /*<<< orphan*/  neigh_list; } ;
struct batadv_neigh_node {int /*<<< orphan*/  list; int /*<<< orphan*/  refcount; struct batadv_hardif_neigh_node* hardif_neigh; int /*<<< orphan*/  last_seen; struct batadv_orig_node* orig_node; struct batadv_hard_iface* if_incoming; int /*<<< orphan*/  addr; int /*<<< orphan*/  ifinfo_lock; int /*<<< orphan*/  ifinfo_list; } ;
struct batadv_hardif_neigh_node {int /*<<< orphan*/  refcount; } ;
struct batadv_hard_iface {TYPE_1__* net_dev; int /*<<< orphan*/  refcount; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_DBG_BATMAN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct batadv_hardif_neigh_node* batadv_hardif_neigh_get_or_create (struct batadv_hard_iface*,int /*<<< orphan*/  const*,struct batadv_orig_node*) ; 
 int /*<<< orphan*/  batadv_hardif_neigh_put (struct batadv_hardif_neigh_node*) ; 
 struct batadv_neigh_node* batadv_neigh_node_get (struct batadv_orig_node*,struct batadv_hard_iface*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct batadv_neigh_node* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct batadv_neigh_node *
batadv_neigh_node_create(struct batadv_orig_node *orig_node,
			 struct batadv_hard_iface *hard_iface,
			 const u8 *neigh_addr)
{
	struct batadv_neigh_node *neigh_node;
	struct batadv_hardif_neigh_node *hardif_neigh = NULL;

	spin_lock_bh(&orig_node->neigh_list_lock);

	neigh_node = batadv_neigh_node_get(orig_node, hard_iface, neigh_addr);
	if (neigh_node)
		goto out;

	hardif_neigh = batadv_hardif_neigh_get_or_create(hard_iface,
							 neigh_addr, orig_node);
	if (!hardif_neigh)
		goto out;

	neigh_node = kzalloc(sizeof(*neigh_node), GFP_ATOMIC);
	if (!neigh_node)
		goto out;

	INIT_HLIST_NODE(&neigh_node->list);
	INIT_HLIST_HEAD(&neigh_node->ifinfo_list);
	spin_lock_init(&neigh_node->ifinfo_lock);

	kref_get(&hard_iface->refcount);
	ether_addr_copy(neigh_node->addr, neigh_addr);
	neigh_node->if_incoming = hard_iface;
	neigh_node->orig_node = orig_node;
	neigh_node->last_seen = jiffies;

	/* increment unique neighbor refcount */
	kref_get(&hardif_neigh->refcount);
	neigh_node->hardif_neigh = hardif_neigh;

	/* extra reference for return */
	kref_init(&neigh_node->refcount);

	kref_get(&neigh_node->refcount);
	hlist_add_head_rcu(&neigh_node->list, &orig_node->neigh_list);

	batadv_dbg(BATADV_DBG_BATMAN, orig_node->bat_priv,
		   "Creating new neighbor %pM for orig_node %pM on interface %s\n",
		   neigh_addr, orig_node->orig, hard_iface->net_dev->name);

out:
	spin_unlock_bh(&orig_node->neigh_list_lock);

	if (hardif_neigh)
		batadv_hardif_neigh_put(hardif_neigh);
	return neigh_node;
}