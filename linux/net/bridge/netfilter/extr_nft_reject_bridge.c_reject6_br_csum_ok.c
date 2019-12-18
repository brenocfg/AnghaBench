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
struct sk_buff {int data; int len; } ;
struct ipv6hdr {scalar_t__ payload_len; int /*<<< orphan*/  nexthdr; } ;
typedef  int __be16 ;

/* Variables and functions */
 int htons (int) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int ipv6_skip_exthdr (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ nf_ip6_checksum (struct sk_buff*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_reject_verify_csum (int /*<<< orphan*/ ) ; 
 scalar_t__ ntohs (scalar_t__) ; 
 scalar_t__ pskb_trim_rcsum (struct sk_buff*,scalar_t__) ; 
 scalar_t__ skb_csum_unnecessary (struct sk_buff*) ; 

__attribute__((used)) static bool reject6_br_csum_ok(struct sk_buff *skb, int hook)
{
	const struct ipv6hdr *ip6h = ipv6_hdr(skb);
	int thoff;
	__be16 fo;
	u8 proto = ip6h->nexthdr;

	if (skb_csum_unnecessary(skb))
		return true;

	if (ip6h->payload_len &&
	    pskb_trim_rcsum(skb, ntohs(ip6h->payload_len) + sizeof(*ip6h)))
		return false;

	ip6h = ipv6_hdr(skb);
	thoff = ipv6_skip_exthdr(skb, ((u8*)(ip6h+1) - skb->data), &proto, &fo);
	if (thoff < 0 || thoff >= skb->len || (fo & htons(~0x7)) != 0)
		return false;

	if (!nf_reject_verify_csum(proto))
		return true;

	return nf_ip6_checksum(skb, hook, thoff, proto) == 0;
}