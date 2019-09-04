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
struct batadv_priv {int dummy; } ;
struct batadv_orig_node {int /*<<< orphan*/  orig; int /*<<< orphan*/  last_ttvn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_DBG_TT ; 
 int /*<<< orphan*/  BATADV_TT_CLIENT_TEMP ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ batadv_bla_is_loopdetect_mac (unsigned char const*) ; 
 int /*<<< orphan*/  batadv_dbg (int /*<<< orphan*/ ,struct batadv_priv*,char*,unsigned char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_print_vid (unsigned short) ; 
 int /*<<< orphan*/  batadv_tt_global_add (struct batadv_priv*,struct batadv_orig_node*,unsigned char const*,unsigned short,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool batadv_tt_add_temporary_global_entry(struct batadv_priv *bat_priv,
					  struct batadv_orig_node *orig_node,
					  const unsigned char *addr,
					  unsigned short vid)
{
	/* ignore loop detect macs, they are not supposed to be in the tt local
	 * data as well.
	 */
	if (batadv_bla_is_loopdetect_mac(addr))
		return false;

	if (!batadv_tt_global_add(bat_priv, orig_node, addr, vid,
				  BATADV_TT_CLIENT_TEMP,
				  atomic_read(&orig_node->last_ttvn)))
		return false;

	batadv_dbg(BATADV_DBG_TT, bat_priv,
		   "Added temporary global client (addr: %pM, vid: %d, orig: %pM)\n",
		   addr, batadv_print_vid(vid), orig_node->orig);

	return true;
}