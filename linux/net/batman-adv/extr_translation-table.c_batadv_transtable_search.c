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
struct batadv_tt_orig_list_entry {struct batadv_orig_node* orig_node; } ;
struct TYPE_2__ {int flags; } ;
struct batadv_tt_local_entry {TYPE_1__ common; } ;
struct batadv_tt_global_entry {int dummy; } ;
struct batadv_priv {int dummy; } ;
struct batadv_orig_node {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int BATADV_TT_CLIENT_PENDING ; 
 scalar_t__ _batadv_is_ap_isolated (struct batadv_tt_local_entry*,struct batadv_tt_global_entry*) ; 
 struct batadv_tt_orig_list_entry* batadv_transtable_best_orig (struct batadv_priv*,struct batadv_tt_global_entry*) ; 
 int /*<<< orphan*/  batadv_tt_global_entry_put (struct batadv_tt_global_entry*) ; 
 struct batadv_tt_global_entry* batadv_tt_global_hash_find (struct batadv_priv*,int /*<<< orphan*/  const*,unsigned short) ; 
 int /*<<< orphan*/  batadv_tt_local_entry_put (struct batadv_tt_local_entry*) ; 
 struct batadv_tt_local_entry* batadv_tt_local_hash_find (struct batadv_priv*,int /*<<< orphan*/  const*,unsigned short) ; 
 scalar_t__ batadv_vlan_ap_isola_get (struct batadv_priv*,unsigned short) ; 
 int /*<<< orphan*/  kref_get_unless_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

struct batadv_orig_node *batadv_transtable_search(struct batadv_priv *bat_priv,
						  const u8 *src,
						  const u8 *addr,
						  unsigned short vid)
{
	struct batadv_tt_local_entry *tt_local_entry = NULL;
	struct batadv_tt_global_entry *tt_global_entry = NULL;
	struct batadv_orig_node *orig_node = NULL;
	struct batadv_tt_orig_list_entry *best_entry;

	if (src && batadv_vlan_ap_isola_get(bat_priv, vid)) {
		tt_local_entry = batadv_tt_local_hash_find(bat_priv, src, vid);
		if (!tt_local_entry ||
		    (tt_local_entry->common.flags & BATADV_TT_CLIENT_PENDING))
			goto out;
	}

	tt_global_entry = batadv_tt_global_hash_find(bat_priv, addr, vid);
	if (!tt_global_entry)
		goto out;

	/* check whether the clients should not communicate due to AP
	 * isolation
	 */
	if (tt_local_entry &&
	    _batadv_is_ap_isolated(tt_local_entry, tt_global_entry))
		goto out;

	rcu_read_lock();
	best_entry = batadv_transtable_best_orig(bat_priv, tt_global_entry);
	/* found anything? */
	if (best_entry)
		orig_node = best_entry->orig_node;
	if (orig_node && !kref_get_unless_zero(&orig_node->refcount))
		orig_node = NULL;
	rcu_read_unlock();

out:
	if (tt_global_entry)
		batadv_tt_global_entry_put(tt_global_entry);
	if (tt_local_entry)
		batadv_tt_local_entry_put(tt_local_entry);

	return orig_node;
}