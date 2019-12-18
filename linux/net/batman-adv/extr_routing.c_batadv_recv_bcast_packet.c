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
typedef  void* u32 ;
struct sk_buff {scalar_t__ data; } ;
struct ethhdr {int /*<<< orphan*/  h_source; int /*<<< orphan*/  h_dest; } ;
struct batadv_priv {int dummy; } ;
struct batadv_orig_node {void* last_bcast_seqno; int /*<<< orphan*/  bcast_seqno_lock; int /*<<< orphan*/  bcast_bits; int /*<<< orphan*/  bcast_seqno_reset; } ;
struct batadv_hard_iface {int /*<<< orphan*/  soft_iface; } ;
struct batadv_bcast_packet {int ttl; int /*<<< orphan*/  seqno; int /*<<< orphan*/  orig; } ;
typedef  void* s32 ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_BCAST_MAX_AGE ; 
 int NET_RX_DROP ; 
 int NET_RX_SUCCESS ; 
 int /*<<< orphan*/  batadv_add_bcast_packet_to_list (struct batadv_priv*,struct sk_buff*,int,int) ; 
 scalar_t__ batadv_bit_get_packet (struct batadv_priv*,int /*<<< orphan*/ ,void*,int) ; 
 scalar_t__ batadv_bla_check_bcast_duplist (struct batadv_priv*,struct sk_buff*) ; 
 scalar_t__ batadv_bla_is_backbone_gw (struct sk_buff*,struct batadv_orig_node*,int) ; 
 scalar_t__ batadv_dat_snoop_incoming_arp_reply (struct batadv_priv*,struct sk_buff*,int) ; 
 scalar_t__ batadv_dat_snoop_incoming_arp_request (struct batadv_priv*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  batadv_dat_snoop_incoming_dhcp_ack (struct batadv_priv*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  batadv_interface_rx (int /*<<< orphan*/ ,struct sk_buff*,int,struct batadv_orig_node*) ; 
 scalar_t__ batadv_is_my_mac (struct batadv_priv*,int /*<<< orphan*/ ) ; 
 struct batadv_orig_node* batadv_orig_hash_find (struct batadv_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_orig_node_put (struct batadv_orig_node*) ; 
 int /*<<< orphan*/  batadv_skb_set_priority (struct sk_buff*,int) ; 
 scalar_t__ batadv_test_bit (int /*<<< orphan*/ ,void*,void*) ; 
 scalar_t__ batadv_window_protected (struct batadv_priv*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ethhdr* eth_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  is_broadcast_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct batadv_priv* netdev_priv (int /*<<< orphan*/ ) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int batadv_recv_bcast_packet(struct sk_buff *skb,
			     struct batadv_hard_iface *recv_if)
{
	struct batadv_priv *bat_priv = netdev_priv(recv_if->soft_iface);
	struct batadv_orig_node *orig_node = NULL;
	struct batadv_bcast_packet *bcast_packet;
	struct ethhdr *ethhdr;
	int hdr_size = sizeof(*bcast_packet);
	int ret = NET_RX_DROP;
	s32 seq_diff;
	u32 seqno;

	/* drop packet if it has not necessary minimum size */
	if (unlikely(!pskb_may_pull(skb, hdr_size)))
		goto free_skb;

	ethhdr = eth_hdr(skb);

	/* packet with broadcast indication but unicast recipient */
	if (!is_broadcast_ether_addr(ethhdr->h_dest))
		goto free_skb;

	/* packet with broadcast/multicast sender address */
	if (is_multicast_ether_addr(ethhdr->h_source))
		goto free_skb;

	/* ignore broadcasts sent by myself */
	if (batadv_is_my_mac(bat_priv, ethhdr->h_source))
		goto free_skb;

	bcast_packet = (struct batadv_bcast_packet *)skb->data;

	/* ignore broadcasts originated by myself */
	if (batadv_is_my_mac(bat_priv, bcast_packet->orig))
		goto free_skb;

	if (bcast_packet->ttl < 2)
		goto free_skb;

	orig_node = batadv_orig_hash_find(bat_priv, bcast_packet->orig);

	if (!orig_node)
		goto free_skb;

	spin_lock_bh(&orig_node->bcast_seqno_lock);

	seqno = ntohl(bcast_packet->seqno);
	/* check whether the packet is a duplicate */
	if (batadv_test_bit(orig_node->bcast_bits, orig_node->last_bcast_seqno,
			    seqno))
		goto spin_unlock;

	seq_diff = seqno - orig_node->last_bcast_seqno;

	/* check whether the packet is old and the host just restarted. */
	if (batadv_window_protected(bat_priv, seq_diff,
				    BATADV_BCAST_MAX_AGE,
				    &orig_node->bcast_seqno_reset, NULL))
		goto spin_unlock;

	/* mark broadcast in flood history, update window position
	 * if required.
	 */
	if (batadv_bit_get_packet(bat_priv, orig_node->bcast_bits, seq_diff, 1))
		orig_node->last_bcast_seqno = seqno;

	spin_unlock_bh(&orig_node->bcast_seqno_lock);

	/* check whether this has been sent by another originator before */
	if (batadv_bla_check_bcast_duplist(bat_priv, skb))
		goto free_skb;

	batadv_skb_set_priority(skb, sizeof(struct batadv_bcast_packet));

	/* rebroadcast packet */
	batadv_add_bcast_packet_to_list(bat_priv, skb, 1, false);

	/* don't hand the broadcast up if it is from an originator
	 * from the same backbone.
	 */
	if (batadv_bla_is_backbone_gw(skb, orig_node, hdr_size))
		goto free_skb;

	if (batadv_dat_snoop_incoming_arp_request(bat_priv, skb, hdr_size))
		goto rx_success;
	if (batadv_dat_snoop_incoming_arp_reply(bat_priv, skb, hdr_size))
		goto rx_success;

	batadv_dat_snoop_incoming_dhcp_ack(bat_priv, skb, hdr_size);

	/* broadcast for me */
	batadv_interface_rx(recv_if->soft_iface, skb, hdr_size, orig_node);

rx_success:
	ret = NET_RX_SUCCESS;
	goto out;

spin_unlock:
	spin_unlock_bh(&orig_node->bcast_seqno_lock);
free_skb:
	kfree_skb(skb);
out:
	if (orig_node)
		batadv_orig_node_put(orig_node);
	return ret;
}