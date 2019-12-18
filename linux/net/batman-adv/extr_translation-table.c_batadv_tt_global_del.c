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
struct batadv_tt_local_entry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct batadv_tt_global_entry {TYPE_1__ common; int /*<<< orphan*/  orig_list; } ;
struct batadv_priv {int dummy; } ;
struct batadv_orig_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  batadv_tt_global_del_orig_list (struct batadv_tt_global_entry*) ; 
 int /*<<< orphan*/  batadv_tt_global_del_orig_node (struct batadv_priv*,struct batadv_tt_global_entry*,struct batadv_orig_node*,char const*) ; 
 int /*<<< orphan*/  batadv_tt_global_del_roaming (struct batadv_priv*,struct batadv_tt_global_entry*,struct batadv_orig_node*,char const*) ; 
 int /*<<< orphan*/  batadv_tt_global_entry_put (struct batadv_tt_global_entry*) ; 
 int /*<<< orphan*/  batadv_tt_global_free (struct batadv_priv*,struct batadv_tt_global_entry*,char const*) ; 
 struct batadv_tt_global_entry* batadv_tt_global_hash_find (struct batadv_priv*,unsigned char const*,unsigned short) ; 
 int /*<<< orphan*/  batadv_tt_local_entry_put (struct batadv_tt_local_entry*) ; 
 struct batadv_tt_local_entry* batadv_tt_local_hash_find (struct batadv_priv*,int /*<<< orphan*/ ,unsigned short) ; 
 scalar_t__ hlist_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void batadv_tt_global_del(struct batadv_priv *bat_priv,
				 struct batadv_orig_node *orig_node,
				 const unsigned char *addr, unsigned short vid,
				 const char *message, bool roaming)
{
	struct batadv_tt_global_entry *tt_global_entry;
	struct batadv_tt_local_entry *local_entry = NULL;

	tt_global_entry = batadv_tt_global_hash_find(bat_priv, addr, vid);
	if (!tt_global_entry)
		goto out;

	if (!roaming) {
		batadv_tt_global_del_orig_node(bat_priv, tt_global_entry,
					       orig_node, message);

		if (hlist_empty(&tt_global_entry->orig_list))
			batadv_tt_global_free(bat_priv, tt_global_entry,
					      message);

		goto out;
	}

	/* if we are deleting a global entry due to a roam
	 * event, there are two possibilities:
	 * 1) the client roamed from node A to node B => if there
	 *    is only one originator left for this client, we mark
	 *    it with BATADV_TT_CLIENT_ROAM, we start a timer and we
	 *    wait for node B to claim it. In case of timeout
	 *    the entry is purged.
	 *
	 *    If there are other originators left, we directly delete
	 *    the originator.
	 * 2) the client roamed to us => we can directly delete
	 *    the global entry, since it is useless now.
	 */
	local_entry = batadv_tt_local_hash_find(bat_priv,
						tt_global_entry->common.addr,
						vid);
	if (local_entry) {
		/* local entry exists, case 2: client roamed to us. */
		batadv_tt_global_del_orig_list(tt_global_entry);
		batadv_tt_global_free(bat_priv, tt_global_entry, message);
	} else {
		/* no local entry exists, case 1: check for roaming */
		batadv_tt_global_del_roaming(bat_priv, tt_global_entry,
					     orig_node, message);
	}

out:
	if (tt_global_entry)
		batadv_tt_global_entry_put(tt_global_entry);
	if (local_entry)
		batadv_tt_local_entry_put(local_entry);
}