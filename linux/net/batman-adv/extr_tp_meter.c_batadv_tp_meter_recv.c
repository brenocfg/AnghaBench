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
struct sk_buff {scalar_t__ data; } ;
struct batadv_priv {int dummy; } ;
struct batadv_icmp_tp_packet {int subtype; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_DBG_TP_METER ; 
#define  BATADV_TP_ACK 129 
#define  BATADV_TP_MSG 128 
 int /*<<< orphan*/  batadv_dbg (int /*<<< orphan*/ ,struct batadv_priv*,char*,int) ; 
 int /*<<< orphan*/  batadv_tp_recv_ack (struct batadv_priv*,struct sk_buff*) ; 
 int /*<<< orphan*/  batadv_tp_recv_msg (struct batadv_priv*,struct sk_buff*) ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 

void batadv_tp_meter_recv(struct batadv_priv *bat_priv, struct sk_buff *skb)
{
	struct batadv_icmp_tp_packet *icmp;

	icmp = (struct batadv_icmp_tp_packet *)skb->data;

	switch (icmp->subtype) {
	case BATADV_TP_MSG:
		batadv_tp_recv_msg(bat_priv, skb);
		break;
	case BATADV_TP_ACK:
		batadv_tp_recv_ack(bat_priv, skb);
		break;
	default:
		batadv_dbg(BATADV_DBG_TP_METER, bat_priv,
			   "Received unknown TP Metric packet type %u\n",
			   icmp->subtype);
	}
	consume_skb(skb);
}