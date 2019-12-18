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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  vid; int /*<<< orphan*/  addr; int /*<<< orphan*/  flags; } ;
struct batadv_tt_local_entry {TYPE_1__ common; } ;
struct batadv_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_DBG_TT ; 
 int /*<<< orphan*/  BATADV_TT_CLIENT_PENDING ; 
 int /*<<< orphan*/  batadv_dbg (int /*<<< orphan*/ ,struct batadv_priv*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  batadv_print_vid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_tt_local_event (struct batadv_priv*,struct batadv_tt_local_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
batadv_tt_local_set_pending(struct batadv_priv *bat_priv,
			    struct batadv_tt_local_entry *tt_local_entry,
			    u16 flags, const char *message)
{
	batadv_tt_local_event(bat_priv, tt_local_entry, flags);

	/* The local client has to be marked as "pending to be removed" but has
	 * to be kept in the table in order to send it in a full table
	 * response issued before the net ttvn increment (consistency check)
	 */
	tt_local_entry->common.flags |= BATADV_TT_CLIENT_PENDING;

	batadv_dbg(BATADV_DBG_TT, bat_priv,
		   "Local tt entry (%pM, vid: %d) pending to be removed: %s\n",
		   tt_local_entry->common.addr,
		   batadv_print_vid(tt_local_entry->common.vid), message);
}