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
typedef  int u16 ;
struct TYPE_4__ {int flags; } ;
struct batadv_tt_local_entry {TYPE_2__ common; } ;
struct TYPE_3__ {int /*<<< orphan*/  local_hash; } ;
struct batadv_priv {TYPE_1__ tt; } ;

/* Variables and functions */
 int BATADV_NO_FLAGS ; 
 int BATADV_TT_CLIENT_DEL ; 
 int BATADV_TT_CLIENT_NEW ; 
 int BATADV_TT_CLIENT_ROAM ; 
 int /*<<< orphan*/  batadv_choose_tt ; 
 int /*<<< orphan*/  batadv_compare_tt ; 
 void* batadv_hash_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  batadv_tt_local_entry_put (struct batadv_tt_local_entry*) ; 
 int /*<<< orphan*/  batadv_tt_local_event (struct batadv_priv*,struct batadv_tt_local_entry*,int) ; 
 struct batadv_tt_local_entry* batadv_tt_local_hash_find (struct batadv_priv*,int /*<<< orphan*/  const*,unsigned short) ; 
 int /*<<< orphan*/  batadv_tt_local_set_pending (struct batadv_priv*,struct batadv_tt_local_entry*,int,char const*) ; 

u16 batadv_tt_local_remove(struct batadv_priv *bat_priv, const u8 *addr,
			   unsigned short vid, const char *message,
			   bool roaming)
{
	struct batadv_tt_local_entry *tt_local_entry;
	u16 flags, curr_flags = BATADV_NO_FLAGS;
	void *tt_entry_exists;

	tt_local_entry = batadv_tt_local_hash_find(bat_priv, addr, vid);
	if (!tt_local_entry)
		goto out;

	curr_flags = tt_local_entry->common.flags;

	flags = BATADV_TT_CLIENT_DEL;
	/* if this global entry addition is due to a roaming, the node has to
	 * mark the local entry as "roamed" in order to correctly reroute
	 * packets later
	 */
	if (roaming) {
		flags |= BATADV_TT_CLIENT_ROAM;
		/* mark the local client as ROAMed */
		tt_local_entry->common.flags |= BATADV_TT_CLIENT_ROAM;
	}

	if (!(tt_local_entry->common.flags & BATADV_TT_CLIENT_NEW)) {
		batadv_tt_local_set_pending(bat_priv, tt_local_entry, flags,
					    message);
		goto out;
	}
	/* if this client has been added right now, it is possible to
	 * immediately purge it
	 */
	batadv_tt_local_event(bat_priv, tt_local_entry, BATADV_TT_CLIENT_DEL);

	tt_entry_exists = batadv_hash_remove(bat_priv->tt.local_hash,
					     batadv_compare_tt,
					     batadv_choose_tt,
					     &tt_local_entry->common);
	if (!tt_entry_exists)
		goto out;

	/* extra call to free the local tt entry */
	batadv_tt_local_entry_put(tt_local_entry);

out:
	if (tt_local_entry)
		batadv_tt_local_entry_put(tt_local_entry);

	return curr_flags;
}