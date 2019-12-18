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
typedef  scalar_t__ u8 ;
struct sk_buff {scalar_t__ len; } ;
struct batadv_priv {int dummy; } ;
struct batadv_ogm_packet {int flags; int /*<<< orphan*/  tvlv_len; int /*<<< orphan*/  ttl; int /*<<< orphan*/  tq; int /*<<< orphan*/  seqno; int /*<<< orphan*/  orig; } ;
struct batadv_hard_iface {scalar_t__ if_status; TYPE_1__* net_dev; int /*<<< orphan*/  soft_iface; } ;
struct batadv_forw_packet {int direct_link_flags; TYPE_2__* skb; int /*<<< orphan*/  own; struct batadv_hard_iface* if_incoming; int /*<<< orphan*/  packet_len; } ;
typedef  int s16 ;
struct TYPE_4__ {scalar_t__* data; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_CNT_MGMT_TX ; 
 int /*<<< orphan*/  BATADV_CNT_MGMT_TX_BYTES ; 
 int /*<<< orphan*/  BATADV_DBG_BATMAN ; 
 int BATADV_DIRECTLINK ; 
 scalar_t__ BATADV_IF_ACTIVE ; 
 int BATADV_OGM_HLEN ; 
 int BIT (scalar_t__) ; 
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  batadv_add_counter (struct batadv_priv*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  batadv_dbg (int /*<<< orphan*/ ,struct batadv_priv*,char*,char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_inc_counter (struct batadv_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ batadv_iv_ogm_aggr_packet (int,int /*<<< orphan*/ ,struct batadv_ogm_packet*) ; 
 int /*<<< orphan*/  batadv_send_broadcast_skb (struct sk_buff*,struct batadv_hard_iface*) ; 
 struct batadv_priv* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_clone (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void batadv_iv_ogm_send_to_if(struct batadv_forw_packet *forw_packet,
				     struct batadv_hard_iface *hard_iface)
{
	struct batadv_priv *bat_priv = netdev_priv(hard_iface->soft_iface);
	const char *fwd_str;
	u8 packet_num;
	s16 buff_pos;
	struct batadv_ogm_packet *batadv_ogm_packet;
	struct sk_buff *skb;
	u8 *packet_pos;

	if (hard_iface->if_status != BATADV_IF_ACTIVE)
		return;

	packet_num = 0;
	buff_pos = 0;
	packet_pos = forw_packet->skb->data;
	batadv_ogm_packet = (struct batadv_ogm_packet *)packet_pos;

	/* adjust all flags and log packets */
	while (batadv_iv_ogm_aggr_packet(buff_pos, forw_packet->packet_len,
					 batadv_ogm_packet)) {
		/* we might have aggregated direct link packets with an
		 * ordinary base packet
		 */
		if (forw_packet->direct_link_flags & BIT(packet_num) &&
		    forw_packet->if_incoming == hard_iface)
			batadv_ogm_packet->flags |= BATADV_DIRECTLINK;
		else
			batadv_ogm_packet->flags &= ~BATADV_DIRECTLINK;

		if (packet_num > 0 || !forw_packet->own)
			fwd_str = "Forwarding";
		else
			fwd_str = "Sending own";

		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "%s %spacket (originator %pM, seqno %u, TQ %d, TTL %d, IDF %s) on interface %s [%pM]\n",
			   fwd_str, (packet_num > 0 ? "aggregated " : ""),
			   batadv_ogm_packet->orig,
			   ntohl(batadv_ogm_packet->seqno),
			   batadv_ogm_packet->tq, batadv_ogm_packet->ttl,
			   ((batadv_ogm_packet->flags & BATADV_DIRECTLINK) ?
			    "on" : "off"),
			   hard_iface->net_dev->name,
			   hard_iface->net_dev->dev_addr);

		buff_pos += BATADV_OGM_HLEN;
		buff_pos += ntohs(batadv_ogm_packet->tvlv_len);
		packet_num++;
		packet_pos = forw_packet->skb->data + buff_pos;
		batadv_ogm_packet = (struct batadv_ogm_packet *)packet_pos;
	}

	/* create clone because function is called more than once */
	skb = skb_clone(forw_packet->skb, GFP_ATOMIC);
	if (skb) {
		batadv_inc_counter(bat_priv, BATADV_CNT_MGMT_TX);
		batadv_add_counter(bat_priv, BATADV_CNT_MGMT_TX_BYTES,
				   skb->len + ETH_HLEN);
		batadv_send_broadcast_skb(skb, hard_iface);
	}
}