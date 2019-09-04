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
struct sk_buff {scalar_t__ data; } ;
struct ethhdr {int /*<<< orphan*/  h_source; } ;
struct batadv_priv {TYPE_1__* algo_ops; } ;
struct batadv_hard_iface {int /*<<< orphan*/  soft_iface; } ;
struct batadv_elp_packet {int /*<<< orphan*/  orig; int /*<<< orphan*/  seqno; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_DBG_BATMAN ; 
 int /*<<< orphan*/  BATADV_ELP_HLEN ; 
 int NET_RX_DROP ; 
 int NET_RX_SUCCESS ; 
 int batadv_check_management_packet (struct sk_buff*,struct batadv_hard_iface*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_dbg (int /*<<< orphan*/ ,struct batadv_priv*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_hardif_put (struct batadv_hard_iface*) ; 
 scalar_t__ batadv_is_my_mac (struct batadv_priv*,int /*<<< orphan*/ ) ; 
 struct batadv_hard_iface* batadv_primary_if_get_selected (struct batadv_priv*) ; 
 int /*<<< orphan*/  batadv_v_elp_neigh_update (struct batadv_priv*,int /*<<< orphan*/ ,struct batadv_hard_iface*,struct batadv_elp_packet*) ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct batadv_priv* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_mac_header (struct sk_buff*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

int batadv_v_elp_packet_recv(struct sk_buff *skb,
			     struct batadv_hard_iface *if_incoming)
{
	struct batadv_priv *bat_priv = netdev_priv(if_incoming->soft_iface);
	struct batadv_elp_packet *elp_packet;
	struct batadv_hard_iface *primary_if;
	struct ethhdr *ethhdr = (struct ethhdr *)skb_mac_header(skb);
	bool res;
	int ret = NET_RX_DROP;

	res = batadv_check_management_packet(skb, if_incoming, BATADV_ELP_HLEN);
	if (!res)
		goto free_skb;

	if (batadv_is_my_mac(bat_priv, ethhdr->h_source))
		goto free_skb;

	/* did we receive a B.A.T.M.A.N. V ELP packet on an interface
	 * that does not have B.A.T.M.A.N. V ELP enabled ?
	 */
	if (strcmp(bat_priv->algo_ops->name, "BATMAN_V") != 0)
		goto free_skb;

	elp_packet = (struct batadv_elp_packet *)skb->data;

	batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
		   "Received ELP packet from %pM seqno %u ORIG: %pM\n",
		   ethhdr->h_source, ntohl(elp_packet->seqno),
		   elp_packet->orig);

	primary_if = batadv_primary_if_get_selected(bat_priv);
	if (!primary_if)
		goto free_skb;

	batadv_v_elp_neigh_update(bat_priv, ethhdr->h_source, if_incoming,
				  elp_packet);

	ret = NET_RX_SUCCESS;
	batadv_hardif_put(primary_if);

free_skb:
	if (ret == NET_RX_SUCCESS)
		consume_skb(skb);
	else
		kfree_skb(skb);

	return ret;
}