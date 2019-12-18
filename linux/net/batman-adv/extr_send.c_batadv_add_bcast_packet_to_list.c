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
struct batadv_priv {int /*<<< orphan*/  bcast_queue_left; } ;
struct batadv_hard_iface {int dummy; } ;
struct batadv_forw_packet {int own; int /*<<< orphan*/  delayed_work; } ;
struct batadv_bcast_packet {int /*<<< orphan*/  ttl; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 struct batadv_forw_packet* batadv_forw_packet_alloc (struct batadv_hard_iface*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct batadv_priv*,struct sk_buff*) ; 
 int /*<<< orphan*/  batadv_forw_packet_bcast_queue (struct batadv_priv*,struct batadv_forw_packet*,scalar_t__) ; 
 int /*<<< orphan*/  batadv_hardif_put (struct batadv_hard_iface*) ; 
 struct batadv_hard_iface* batadv_primary_if_get_selected (struct batadv_priv*) ; 
 int /*<<< orphan*/  batadv_send_outstanding_bcast_packet ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* skb_copy (struct sk_buff const*,int /*<<< orphan*/ ) ; 

int batadv_add_bcast_packet_to_list(struct batadv_priv *bat_priv,
				    const struct sk_buff *skb,
				    unsigned long delay,
				    bool own_packet)
{
	struct batadv_hard_iface *primary_if;
	struct batadv_forw_packet *forw_packet;
	struct batadv_bcast_packet *bcast_packet;
	struct sk_buff *newskb;

	primary_if = batadv_primary_if_get_selected(bat_priv);
	if (!primary_if)
		goto err;

	newskb = skb_copy(skb, GFP_ATOMIC);
	if (!newskb) {
		batadv_hardif_put(primary_if);
		goto err;
	}

	forw_packet = batadv_forw_packet_alloc(primary_if, NULL,
					       &bat_priv->bcast_queue_left,
					       bat_priv, newskb);
	batadv_hardif_put(primary_if);
	if (!forw_packet)
		goto err_packet_free;

	/* as we have a copy now, it is safe to decrease the TTL */
	bcast_packet = (struct batadv_bcast_packet *)newskb->data;
	bcast_packet->ttl--;

	forw_packet->own = own_packet;

	INIT_DELAYED_WORK(&forw_packet->delayed_work,
			  batadv_send_outstanding_bcast_packet);

	batadv_forw_packet_bcast_queue(bat_priv, forw_packet, jiffies + delay);
	return NETDEV_TX_OK;

err_packet_free:
	kfree_skb(newskb);
err:
	return NETDEV_TX_BUSY;
}