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
struct sk_buff {scalar_t__ protocol; scalar_t__ data; } ;
struct nshhdr {int /*<<< orphan*/  np; } ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int ENOMEM ; 
 size_t NSH_BASE_HDR_LEN ; 
 size_t nsh_hdr_len (struct nshhdr*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  skb_pull_rcsum (struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_mac_len (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 scalar_t__ tun_p_to_eth_p (int /*<<< orphan*/ ) ; 

int nsh_pop(struct sk_buff *skb)
{
	struct nshhdr *nh;
	size_t length;
	__be16 inner_proto;

	if (!pskb_may_pull(skb, NSH_BASE_HDR_LEN))
		return -ENOMEM;
	nh = (struct nshhdr *)(skb->data);
	length = nsh_hdr_len(nh);
	if (length < NSH_BASE_HDR_LEN)
		return -EINVAL;
	inner_proto = tun_p_to_eth_p(nh->np);
	if (!pskb_may_pull(skb, length))
		return -ENOMEM;

	if (!inner_proto)
		return -EAFNOSUPPORT;

	skb_pull_rcsum(skb, length);
	skb_reset_mac_header(skb);
	skb_reset_network_header(skb);
	skb_reset_mac_len(skb);
	skb->protocol = inner_proto;

	return 0;
}