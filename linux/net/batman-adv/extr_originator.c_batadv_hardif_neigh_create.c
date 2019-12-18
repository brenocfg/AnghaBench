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
typedef  int /*<<< orphan*/  u8 ;
struct batadv_priv {TYPE_2__* algo_ops; } ;
struct batadv_orig_node {int /*<<< orphan*/  const* orig; } ;
struct batadv_hardif_neigh_node {int /*<<< orphan*/  list; int /*<<< orphan*/  refcount; int /*<<< orphan*/  last_seen; struct batadv_hard_iface* if_incoming; int /*<<< orphan*/  orig; int /*<<< orphan*/  addr; } ;
struct batadv_hard_iface {int /*<<< orphan*/  neigh_list_lock; int /*<<< orphan*/  neigh_list; int /*<<< orphan*/  refcount; int /*<<< orphan*/  soft_iface; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* hardif_init ) (struct batadv_hardif_neigh_node*) ;} ;
struct TYPE_4__ {TYPE_1__ neigh; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 struct batadv_hardif_neigh_node* batadv_hardif_neigh_get (struct batadv_hard_iface*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct batadv_hardif_neigh_node* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct batadv_priv* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct batadv_hardif_neigh_node*) ; 

__attribute__((used)) static struct batadv_hardif_neigh_node *
batadv_hardif_neigh_create(struct batadv_hard_iface *hard_iface,
			   const u8 *neigh_addr,
			   struct batadv_orig_node *orig_node)
{
	struct batadv_priv *bat_priv = netdev_priv(hard_iface->soft_iface);
	struct batadv_hardif_neigh_node *hardif_neigh;

	spin_lock_bh(&hard_iface->neigh_list_lock);

	/* check if neighbor hasn't been added in the meantime */
	hardif_neigh = batadv_hardif_neigh_get(hard_iface, neigh_addr);
	if (hardif_neigh)
		goto out;

	hardif_neigh = kzalloc(sizeof(*hardif_neigh), GFP_ATOMIC);
	if (!hardif_neigh)
		goto out;

	kref_get(&hard_iface->refcount);
	INIT_HLIST_NODE(&hardif_neigh->list);
	ether_addr_copy(hardif_neigh->addr, neigh_addr);
	ether_addr_copy(hardif_neigh->orig, orig_node->orig);
	hardif_neigh->if_incoming = hard_iface;
	hardif_neigh->last_seen = jiffies;

	kref_init(&hardif_neigh->refcount);

	if (bat_priv->algo_ops->neigh.hardif_init)
		bat_priv->algo_ops->neigh.hardif_init(hardif_neigh);

	hlist_add_head_rcu(&hardif_neigh->list, &hard_iface->neigh_list);

out:
	spin_unlock_bh(&hard_iface->neigh_list_lock);
	return hardif_neigh;
}