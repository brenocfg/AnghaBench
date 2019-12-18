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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct batadv_tp_vars {int dummy; } ;
struct batadv_orig_node {int /*<<< orphan*/  const* orig; } ;
struct batadv_icmp_tp_packet {int uid; void* timestamp; void* seqno; int /*<<< orphan*/  session; int /*<<< orphan*/  subtype; int /*<<< orphan*/  msg_type; int /*<<< orphan*/  ttl; int /*<<< orphan*/  packet_type; int /*<<< orphan*/  version; int /*<<< orphan*/  orig; int /*<<< orphan*/  dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_COMPAT_VERSION ; 
 int /*<<< orphan*/  BATADV_ICMP ; 
 int /*<<< orphan*/  BATADV_TP ; 
 int /*<<< orphan*/  BATADV_TP_MSG ; 
 int BATADV_TP_REASON_CANT_SEND ; 
 int BATADV_TP_REASON_MEMORY_ERROR ; 
 int /*<<< orphan*/  BATADV_TTL ; 
 scalar_t__ ETH_HLEN ; 
 int NET_XMIT_SUCCESS ; 
 int batadv_send_skb_to_orig (struct sk_buff*,struct batadv_orig_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_tp_fill_prerandom (struct batadv_tp_vars*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 struct sk_buff* netdev_alloc_skb_ip_align (int /*<<< orphan*/ *,scalar_t__) ; 
 void* skb_put (struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int batadv_tp_send_msg(struct batadv_tp_vars *tp_vars, const u8 *src,
			      struct batadv_orig_node *orig_node,
			      u32 seqno, size_t len, const u8 *session,
			      int uid, u32 timestamp)
{
	struct batadv_icmp_tp_packet *icmp;
	struct sk_buff *skb;
	int r;
	u8 *data;
	size_t data_len;

	skb = netdev_alloc_skb_ip_align(NULL, len + ETH_HLEN);
	if (unlikely(!skb))
		return BATADV_TP_REASON_MEMORY_ERROR;

	skb_reserve(skb, ETH_HLEN);
	icmp = skb_put(skb, sizeof(*icmp));

	/* fill the icmp header */
	ether_addr_copy(icmp->dst, orig_node->orig);
	ether_addr_copy(icmp->orig, src);
	icmp->version = BATADV_COMPAT_VERSION;
	icmp->packet_type = BATADV_ICMP;
	icmp->ttl = BATADV_TTL;
	icmp->msg_type = BATADV_TP;
	icmp->uid = uid;

	icmp->subtype = BATADV_TP_MSG;
	memcpy(icmp->session, session, sizeof(icmp->session));
	icmp->seqno = htonl(seqno);
	icmp->timestamp = htonl(timestamp);

	data_len = len - sizeof(*icmp);
	data = skb_put(skb, data_len);
	batadv_tp_fill_prerandom(tp_vars, data, data_len);

	r = batadv_send_skb_to_orig(skb, orig_node, NULL);
	if (r == NET_XMIT_SUCCESS)
		return 0;

	return BATADV_TP_REASON_CANT_SEND;
}