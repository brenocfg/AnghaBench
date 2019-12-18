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
struct sk_buff {scalar_t__ encapsulation; } ;
struct ipv6_sr_hdr {scalar_t__ segments_left; } ;

/* Variables and functions */
 struct ipv6_sr_hdr* get_srh (struct sk_buff*) ; 
 scalar_t__ ipv6_find_hdr (struct sk_buff*,unsigned int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pskb_pull (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  seg6_hmac_validate_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_postpull_rcsum (struct sk_buff*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 

__attribute__((used)) static bool decap_and_validate(struct sk_buff *skb, int proto)
{
	struct ipv6_sr_hdr *srh;
	unsigned int off = 0;

	srh = get_srh(skb);
	if (srh && srh->segments_left > 0)
		return false;

#ifdef CONFIG_IPV6_SEG6_HMAC
	if (srh && !seg6_hmac_validate_skb(skb))
		return false;
#endif

	if (ipv6_find_hdr(skb, &off, proto, NULL, NULL) < 0)
		return false;

	if (!pskb_pull(skb, off))
		return false;

	skb_postpull_rcsum(skb, skb_network_header(skb), off);

	skb_reset_network_header(skb);
	skb_reset_transport_header(skb);
	skb->encapsulation = 0;

	return true;
}