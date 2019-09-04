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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct batadv_priv {int dummy; } ;
struct batadv_orig_node {TYPE_1__* net_dev; int /*<<< orphan*/  orig; } ;
struct batadv_icmp_tp_packet {int uid; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  seqno; int /*<<< orphan*/  session; int /*<<< orphan*/  subtype; int /*<<< orphan*/  orig; int /*<<< orphan*/  dst; int /*<<< orphan*/  msg_type; int /*<<< orphan*/  ttl; int /*<<< orphan*/  version; int /*<<< orphan*/  packet_type; } ;
struct batadv_hard_iface {TYPE_1__* net_dev; int /*<<< orphan*/  orig; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_COMPAT_VERSION ; 
 int /*<<< orphan*/  BATADV_ICMP ; 
 int /*<<< orphan*/  BATADV_TP ; 
 int /*<<< orphan*/  BATADV_TP_ACK ; 
 int BATADV_TP_REASON_DST_UNREACHABLE ; 
 int BATADV_TP_REASON_MEMORY_ERROR ; 
 int /*<<< orphan*/  BATADV_TTL ; 
 scalar_t__ ETH_HLEN ; 
 int NET_XMIT_DROP ; 
 int /*<<< orphan*/  batadv_hardif_put (struct batadv_orig_node*) ; 
 struct batadv_orig_node* batadv_orig_hash_find (struct batadv_priv*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  batadv_orig_node_put (struct batadv_orig_node*) ; 
 struct batadv_orig_node* batadv_primary_if_get_selected (struct batadv_priv*) ; 
 int batadv_send_skb_to_orig (struct sk_buff*,struct batadv_orig_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (struct batadv_orig_node*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 struct sk_buff* netdev_alloc_skb_ip_align (int /*<<< orphan*/ *,scalar_t__) ; 
 struct batadv_icmp_tp_packet* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int batadv_tp_send_ack(struct batadv_priv *bat_priv, const u8 *dst,
			      u32 seq, __be32 timestamp, const u8 *session,
			      int socket_index)
{
	struct batadv_hard_iface *primary_if = NULL;
	struct batadv_orig_node *orig_node;
	struct batadv_icmp_tp_packet *icmp;
	struct sk_buff *skb;
	int r, ret;

	orig_node = batadv_orig_hash_find(bat_priv, dst);
	if (unlikely(!orig_node)) {
		ret = BATADV_TP_REASON_DST_UNREACHABLE;
		goto out;
	}

	primary_if = batadv_primary_if_get_selected(bat_priv);
	if (unlikely(!primary_if)) {
		ret = BATADV_TP_REASON_DST_UNREACHABLE;
		goto out;
	}

	skb = netdev_alloc_skb_ip_align(NULL, sizeof(*icmp) + ETH_HLEN);
	if (unlikely(!skb)) {
		ret = BATADV_TP_REASON_MEMORY_ERROR;
		goto out;
	}

	skb_reserve(skb, ETH_HLEN);
	icmp = skb_put(skb, sizeof(*icmp));
	icmp->packet_type = BATADV_ICMP;
	icmp->version = BATADV_COMPAT_VERSION;
	icmp->ttl = BATADV_TTL;
	icmp->msg_type = BATADV_TP;
	ether_addr_copy(icmp->dst, orig_node->orig);
	ether_addr_copy(icmp->orig, primary_if->net_dev->dev_addr);
	icmp->uid = socket_index;

	icmp->subtype = BATADV_TP_ACK;
	memcpy(icmp->session, session, sizeof(icmp->session));
	icmp->seqno = htonl(seq);
	icmp->timestamp = timestamp;

	/* send the ack */
	r = batadv_send_skb_to_orig(skb, orig_node, NULL);
	if (unlikely(r < 0) || r == NET_XMIT_DROP) {
		ret = BATADV_TP_REASON_DST_UNREACHABLE;
		goto out;
	}
	ret = 0;

out:
	if (likely(orig_node))
		batadv_orig_node_put(orig_node);
	if (likely(primary_if))
		batadv_hardif_put(primary_if);

	return ret;
}