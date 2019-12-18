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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct batadv_tvlv_tt_change {int flags; int /*<<< orphan*/  vid; int /*<<< orphan*/  addr; } ;
struct batadv_priv {int dummy; } ;
struct batadv_orig_node {int /*<<< orphan*/  capa_initialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_ORIG_CAPA_HAS_TT ; 
 int BATADV_TT_CLIENT_DEL ; 
 int BATADV_TT_CLIENT_ROAM ; 
 int /*<<< orphan*/  batadv_tt_global_add (struct batadv_priv*,struct batadv_orig_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_tt_global_del (struct batadv_priv*,struct batadv_orig_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _batadv_tt_update_changes(struct batadv_priv *bat_priv,
				      struct batadv_orig_node *orig_node,
				      struct batadv_tvlv_tt_change *tt_change,
				      u16 tt_num_changes, u8 ttvn)
{
	int i;
	int roams;

	for (i = 0; i < tt_num_changes; i++) {
		if ((tt_change + i)->flags & BATADV_TT_CLIENT_DEL) {
			roams = (tt_change + i)->flags & BATADV_TT_CLIENT_ROAM;
			batadv_tt_global_del(bat_priv, orig_node,
					     (tt_change + i)->addr,
					     ntohs((tt_change + i)->vid),
					     "tt removed by changes",
					     roams);
		} else {
			if (!batadv_tt_global_add(bat_priv, orig_node,
						  (tt_change + i)->addr,
						  ntohs((tt_change + i)->vid),
						  (tt_change + i)->flags, ttvn))
				/* In case of problem while storing a
				 * global_entry, we stop the updating
				 * procedure without committing the
				 * ttvn change. This will avoid to send
				 * corrupted data on tt_request
				 */
				return;
		}
	}
	set_bit(BATADV_ORIG_CAPA_HAS_TT, &orig_node->capa_initialized);
}