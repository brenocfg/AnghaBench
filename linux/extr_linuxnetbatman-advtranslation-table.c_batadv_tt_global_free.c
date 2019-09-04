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
struct TYPE_4__ {int /*<<< orphan*/  vid; int /*<<< orphan*/  addr; } ;
struct batadv_tt_global_entry {TYPE_2__ common; } ;
struct TYPE_3__ {int /*<<< orphan*/  global_hash; } ;
struct batadv_priv {TYPE_1__ tt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_DBG_TT ; 
 int /*<<< orphan*/  batadv_choose_tt ; 
 int /*<<< orphan*/  batadv_compare_tt ; 
 int /*<<< orphan*/  batadv_dbg (int /*<<< orphan*/ ,struct batadv_priv*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  batadv_hash_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  batadv_print_vid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_tt_global_entry_put (struct batadv_tt_global_entry*) ; 

__attribute__((used)) static void batadv_tt_global_free(struct batadv_priv *bat_priv,
				  struct batadv_tt_global_entry *tt_global,
				  const char *message)
{
	batadv_dbg(BATADV_DBG_TT, bat_priv,
		   "Deleting global tt entry %pM (vid: %d): %s\n",
		   tt_global->common.addr,
		   batadv_print_vid(tt_global->common.vid), message);

	batadv_hash_remove(bat_priv->tt.global_hash, batadv_compare_tt,
			   batadv_choose_tt, &tt_global->common);
	batadv_tt_global_entry_put(tt_global);
}