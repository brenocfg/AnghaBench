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

/* Variables and functions */
 int /*<<< orphan*/  calipso_validate (struct sk_buff*,unsigned char const*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 unsigned char* skb_network_header (struct sk_buff*) ; 

__attribute__((used)) static bool ipv6_hop_calipso(struct sk_buff *skb, int optoff)
{
	const unsigned char *nh = skb_network_header(skb);

	if (nh[optoff + 1] < 8)
		goto drop;

	if (nh[optoff + 6] * 4 + 8 > nh[optoff + 1])
		goto drop;

	if (!calipso_validate(skb, nh + optoff))
		goto drop;

	return true;

drop:
	kfree_skb(skb);
	return false;
}