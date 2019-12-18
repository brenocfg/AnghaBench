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
typedef  unsigned int u8 ;
typedef  unsigned int u16 ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {int len; unsigned int* data; int /*<<< orphan*/  priority; int /*<<< orphan*/  dev; scalar_t__ head_frag; } ;
struct ethhdr {int /*<<< orphan*/  h_proto; int /*<<< orphan*/  h_source; int /*<<< orphan*/  h_dest; } ;
typedef  int /*<<< orphan*/  eth ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;

/* Variables and functions */
 unsigned int ALIGN (unsigned int const,int) ; 
 int ETH_ALEN ; 
 unsigned int ETH_P_AARP ; 
 unsigned int ETH_P_IPX ; 
 struct sk_buff* __ieee80211_amsdu_copy (struct sk_buff*,unsigned int,int,int,int) ; 
 int /*<<< orphan*/  __skb_queue_purge (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 int /*<<< orphan*/  bridge_tunnel_header ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 scalar_t__ ether_addr_equal (unsigned int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (unsigned int) ; 
 int /*<<< orphan*/  is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct ethhdr*,int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfc1042_header ; 
 int /*<<< orphan*/  skb_copy_bits (struct sk_buff*,int,struct ethhdr*,int) ; 
 int /*<<< orphan*/  skb_has_frag_list (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_is_nonlinear (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 

void ieee80211_amsdu_to_8023s(struct sk_buff *skb, struct sk_buff_head *list,
			      const u8 *addr, enum nl80211_iftype iftype,
			      const unsigned int extra_headroom,
			      const u8 *check_da, const u8 *check_sa)
{
	unsigned int hlen = ALIGN(extra_headroom, 4);
	struct sk_buff *frame = NULL;
	u16 ethertype;
	u8 *payload;
	int offset = 0, remaining;
	struct ethhdr eth;
	bool reuse_frag = skb->head_frag && !skb_has_frag_list(skb);
	bool reuse_skb = false;
	bool last = false;

	while (!last) {
		unsigned int subframe_len;
		int len;
		u8 padding;

		skb_copy_bits(skb, offset, &eth, sizeof(eth));
		len = ntohs(eth.h_proto);
		subframe_len = sizeof(struct ethhdr) + len;
		padding = (4 - subframe_len) & 0x3;

		/* the last MSDU has no padding */
		remaining = skb->len - offset;
		if (subframe_len > remaining)
			goto purge;

		offset += sizeof(struct ethhdr);
		last = remaining <= subframe_len + padding;

		/* FIXME: should we really accept multicast DA? */
		if ((check_da && !is_multicast_ether_addr(eth.h_dest) &&
		     !ether_addr_equal(check_da, eth.h_dest)) ||
		    (check_sa && !ether_addr_equal(check_sa, eth.h_source))) {
			offset += len + padding;
			continue;
		}

		/* reuse skb for the last subframe */
		if (!skb_is_nonlinear(skb) && !reuse_frag && last) {
			skb_pull(skb, offset);
			frame = skb;
			reuse_skb = true;
		} else {
			frame = __ieee80211_amsdu_copy(skb, hlen, offset, len,
						       reuse_frag);
			if (!frame)
				goto purge;

			offset += len + padding;
		}

		skb_reset_network_header(frame);
		frame->dev = skb->dev;
		frame->priority = skb->priority;

		payload = frame->data;
		ethertype = (payload[6] << 8) | payload[7];
		if (likely((ether_addr_equal(payload, rfc1042_header) &&
			    ethertype != ETH_P_AARP && ethertype != ETH_P_IPX) ||
			   ether_addr_equal(payload, bridge_tunnel_header))) {
			eth.h_proto = htons(ethertype);
			skb_pull(frame, ETH_ALEN + 2);
		}

		memcpy(skb_push(frame, sizeof(eth)), &eth, sizeof(eth));
		__skb_queue_tail(list, frame);
	}

	if (!reuse_skb)
		dev_kfree_skb(skb);

	return;

 purge:
	__skb_queue_purge(list);
	dev_kfree_skb(skb);
}