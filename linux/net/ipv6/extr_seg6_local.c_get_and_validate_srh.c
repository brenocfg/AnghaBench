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
struct sk_buff {int dummy; } ;
struct ipv6_sr_hdr {scalar_t__ segments_left; } ;

/* Variables and functions */
 struct ipv6_sr_hdr* get_srh (struct sk_buff*) ; 
 int /*<<< orphan*/  seg6_hmac_validate_skb (struct sk_buff*) ; 

__attribute__((used)) static struct ipv6_sr_hdr *get_and_validate_srh(struct sk_buff *skb)
{
	struct ipv6_sr_hdr *srh;

	srh = get_srh(skb);
	if (!srh)
		return NULL;

	if (srh->segments_left == 0)
		return NULL;

#ifdef CONFIG_IPV6_SEG6_HMAC
	if (!seg6_hmac_validate_skb(skb))
		return NULL;
#endif

	return srh;
}