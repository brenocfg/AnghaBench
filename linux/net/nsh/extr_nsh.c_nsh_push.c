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
typedef  scalar_t__ u8 ;
struct sk_buff {int /*<<< orphan*/  protocol; scalar_t__ data; scalar_t__ mac_len; } ;
struct nshhdr {scalar_t__ np; } ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_P_NSH ; 
 scalar_t__ TUN_P_ETHERNET ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct nshhdr*,struct nshhdr const*,size_t) ; 
 size_t nsh_hdr_len (struct nshhdr const*) ; 
 scalar_t__ skb_cow_head (struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  skb_postpush_rcsum (struct sk_buff*,struct nshhdr*,size_t) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_mac_len (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 scalar_t__ tun_p_from_eth_p (int /*<<< orphan*/ ) ; 

int nsh_push(struct sk_buff *skb, const struct nshhdr *pushed_nh)
{
	struct nshhdr *nh;
	size_t length = nsh_hdr_len(pushed_nh);
	u8 next_proto;

	if (skb->mac_len) {
		next_proto = TUN_P_ETHERNET;
	} else {
		next_proto = tun_p_from_eth_p(skb->protocol);
		if (!next_proto)
			return -EAFNOSUPPORT;
	}

	/* Add the NSH header */
	if (skb_cow_head(skb, length) < 0)
		return -ENOMEM;

	skb_push(skb, length);
	nh = (struct nshhdr *)(skb->data);
	memcpy(nh, pushed_nh, length);
	nh->np = next_proto;
	skb_postpush_rcsum(skb, nh, length);

	skb->protocol = htons(ETH_P_NSH);
	skb_reset_mac_header(skb);
	skb_reset_network_header(skb);
	skb_reset_mac_len(skb);

	return 0;
}