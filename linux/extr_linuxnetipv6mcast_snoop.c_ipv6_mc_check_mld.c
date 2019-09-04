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
 int __ipv6_mc_check_mld (struct sk_buff*,struct sk_buff**) ; 
 int ipv6_mc_check_exthdrs (struct sk_buff*) ; 
 int ipv6_mc_check_ip6hdr (struct sk_buff*) ; 

int ipv6_mc_check_mld(struct sk_buff *skb, struct sk_buff **skb_trimmed)
{
	int ret;

	ret = ipv6_mc_check_ip6hdr(skb);
	if (ret < 0)
		return ret;

	ret = ipv6_mc_check_exthdrs(skb);
	if (ret < 0)
		return ret;

	return __ipv6_mc_check_mld(skb, skb_trimmed);
}