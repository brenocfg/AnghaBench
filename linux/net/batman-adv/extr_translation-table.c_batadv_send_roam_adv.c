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
typedef  int /*<<< orphan*/  tvlv_roam ;
struct batadv_tvlv_roam_adv {int /*<<< orphan*/  vid; int /*<<< orphan*/  client; } ;
struct batadv_priv {int dummy; } ;
struct batadv_orig_node {int /*<<< orphan*/  orig; } ;
struct batadv_hard_iface {TYPE_1__* net_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_CNT_TT_ROAM_ADV_TX ; 
 int /*<<< orphan*/  BATADV_DBG_TT ; 
 int /*<<< orphan*/  BATADV_TVLV_ROAM ; 
 int /*<<< orphan*/  batadv_dbg (int /*<<< orphan*/ ,struct batadv_priv*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_hardif_put (struct batadv_hard_iface*) ; 
 int /*<<< orphan*/  batadv_inc_counter (struct batadv_priv*,int /*<<< orphan*/ ) ; 
 struct batadv_hard_iface* batadv_primary_if_get_selected (struct batadv_priv*) ; 
 int /*<<< orphan*/  batadv_print_vid (unsigned short) ; 
 int /*<<< orphan*/  batadv_tt_check_roam_count (struct batadv_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_tvlv_unicast_send (struct batadv_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct batadv_tvlv_roam_adv*,int) ; 
 int /*<<< orphan*/  htons (unsigned short) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void batadv_send_roam_adv(struct batadv_priv *bat_priv, u8 *client,
				 unsigned short vid,
				 struct batadv_orig_node *orig_node)
{
	struct batadv_hard_iface *primary_if;
	struct batadv_tvlv_roam_adv tvlv_roam;

	primary_if = batadv_primary_if_get_selected(bat_priv);
	if (!primary_if)
		goto out;

	/* before going on we have to check whether the client has
	 * already roamed to us too many times
	 */
	if (!batadv_tt_check_roam_count(bat_priv, client))
		goto out;

	batadv_dbg(BATADV_DBG_TT, bat_priv,
		   "Sending ROAMING_ADV to %pM (client %pM, vid: %d)\n",
		   orig_node->orig, client, batadv_print_vid(vid));

	batadv_inc_counter(bat_priv, BATADV_CNT_TT_ROAM_ADV_TX);

	memcpy(tvlv_roam.client, client, sizeof(tvlv_roam.client));
	tvlv_roam.vid = htons(vid);

	batadv_tvlv_unicast_send(bat_priv, primary_if->net_dev->dev_addr,
				 orig_node->orig, BATADV_TVLV_ROAM, 1,
				 &tvlv_roam, sizeof(tvlv_roam));

out:
	if (primary_if)
		batadv_hardif_put(primary_if);
}