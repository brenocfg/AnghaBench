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
struct batadv_priv {int dummy; } ;
struct batadv_orig_node_vlan {int dummy; } ;
struct batadv_orig_node {int last_seen; unsigned long bcast_seqno_reset; TYPE_1__* fragments; int /*<<< orphan*/  mcast_handler_lock; int /*<<< orphan*/  mcast_want_all_ipv6_node; int /*<<< orphan*/  mcast_want_all_ipv4_node; int /*<<< orphan*/  mcast_want_all_unsnoopables_node; int /*<<< orphan*/  mcast_flags; scalar_t__ tt_buff_len; int /*<<< orphan*/ * tt_buff; int /*<<< orphan*/  last_ttvn; int /*<<< orphan*/  orig; struct batadv_priv* bat_priv; int /*<<< orphan*/  refcount; int /*<<< orphan*/  vlan_list_lock; int /*<<< orphan*/  tt_lock; int /*<<< orphan*/  tt_buff_lock; int /*<<< orphan*/  neigh_list_lock; int /*<<< orphan*/  bcast_seqno_lock; int /*<<< orphan*/  ifinfo_list; int /*<<< orphan*/  vlan_list; int /*<<< orphan*/  neigh_list; } ;
struct TYPE_2__ {scalar_t__ size; int /*<<< orphan*/  lock; int /*<<< orphan*/  fragment_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_DBG_BATMAN ; 
 int BATADV_FRAG_BUFFER_COUNT ; 
 int /*<<< orphan*/  BATADV_MCAST_WANT_NO_RTR4 ; 
 int /*<<< orphan*/  BATADV_MCAST_WANT_NO_RTR6 ; 
 int /*<<< orphan*/  BATADV_NO_FLAGS ; 
 int /*<<< orphan*/  BATADV_RESET_PROTECTION_MS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_dat_init_orig_node_addr (struct batadv_orig_node*) ; 
 int /*<<< orphan*/  batadv_dbg (int /*<<< orphan*/ ,struct batadv_priv*,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  batadv_nc_init_orig (struct batadv_orig_node*) ; 
 struct batadv_orig_node_vlan* batadv_orig_node_vlan_new (struct batadv_orig_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_orig_node_vlan_put (struct batadv_orig_node_vlan*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int jiffies ; 
 int /*<<< orphan*/  kfree (struct batadv_orig_node*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct batadv_orig_node* kzalloc (int,int /*<<< orphan*/ ) ; 
 int msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct batadv_orig_node *batadv_orig_node_new(struct batadv_priv *bat_priv,
					      const u8 *addr)
{
	struct batadv_orig_node *orig_node;
	struct batadv_orig_node_vlan *vlan;
	unsigned long reset_time;
	int i;

	batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
		   "Creating new originator: %pM\n", addr);

	orig_node = kzalloc(sizeof(*orig_node), GFP_ATOMIC);
	if (!orig_node)
		return NULL;

	INIT_HLIST_HEAD(&orig_node->neigh_list);
	INIT_HLIST_HEAD(&orig_node->vlan_list);
	INIT_HLIST_HEAD(&orig_node->ifinfo_list);
	spin_lock_init(&orig_node->bcast_seqno_lock);
	spin_lock_init(&orig_node->neigh_list_lock);
	spin_lock_init(&orig_node->tt_buff_lock);
	spin_lock_init(&orig_node->tt_lock);
	spin_lock_init(&orig_node->vlan_list_lock);

	batadv_nc_init_orig(orig_node);

	/* extra reference for return */
	kref_init(&orig_node->refcount);

	orig_node->bat_priv = bat_priv;
	ether_addr_copy(orig_node->orig, addr);
	batadv_dat_init_orig_node_addr(orig_node);
	atomic_set(&orig_node->last_ttvn, 0);
	orig_node->tt_buff = NULL;
	orig_node->tt_buff_len = 0;
	orig_node->last_seen = jiffies;
	reset_time = jiffies - 1 - msecs_to_jiffies(BATADV_RESET_PROTECTION_MS);
	orig_node->bcast_seqno_reset = reset_time;

#ifdef CONFIG_BATMAN_ADV_MCAST
	orig_node->mcast_flags = BATADV_MCAST_WANT_NO_RTR4;
	orig_node->mcast_flags |= BATADV_MCAST_WANT_NO_RTR6;
	INIT_HLIST_NODE(&orig_node->mcast_want_all_unsnoopables_node);
	INIT_HLIST_NODE(&orig_node->mcast_want_all_ipv4_node);
	INIT_HLIST_NODE(&orig_node->mcast_want_all_ipv6_node);
	spin_lock_init(&orig_node->mcast_handler_lock);
#endif

	/* create a vlan object for the "untagged" LAN */
	vlan = batadv_orig_node_vlan_new(orig_node, BATADV_NO_FLAGS);
	if (!vlan)
		goto free_orig_node;
	/* batadv_orig_node_vlan_new() increases the refcounter.
	 * Immediately release vlan since it is not needed anymore in this
	 * context
	 */
	batadv_orig_node_vlan_put(vlan);

	for (i = 0; i < BATADV_FRAG_BUFFER_COUNT; i++) {
		INIT_HLIST_HEAD(&orig_node->fragments[i].fragment_list);
		spin_lock_init(&orig_node->fragments[i].lock);
		orig_node->fragments[i].size = 0;
	}

	return orig_node;
free_orig_node:
	kfree(orig_node);
	return NULL;
}