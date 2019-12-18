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
struct TYPE_2__ {int flags; } ;
struct batadv_tt_local_entry {TYPE_1__ common; } ;
struct batadv_priv {int dummy; } ;

/* Variables and functions */
 int BATADV_TT_CLIENT_ROAM ; 
 int /*<<< orphan*/  batadv_tt_local_entry_put (struct batadv_tt_local_entry*) ; 
 struct batadv_tt_local_entry* batadv_tt_local_hash_find (struct batadv_priv*,int /*<<< orphan*/ *,unsigned short) ; 

bool batadv_tt_local_client_is_roaming(struct batadv_priv *bat_priv,
				       u8 *addr, unsigned short vid)
{
	struct batadv_tt_local_entry *tt_local_entry;
	bool ret = false;

	tt_local_entry = batadv_tt_local_hash_find(bat_priv, addr, vid);
	if (!tt_local_entry)
		goto out;

	ret = tt_local_entry->common.flags & BATADV_TT_CLIENT_ROAM;
	batadv_tt_local_entry_put(tt_local_entry);
out:
	return ret;
}