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
struct __sk_buff {scalar_t__ protocol; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int TC_ACT_OK ; 
 scalar_t__ __bpf_constant_htons (int /*<<< orphan*/ ) ; 
 int encap_ipv6 (struct __sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int __encap_ip6tnl_none(struct __sk_buff *skb)
{
	if (skb->protocol == __bpf_constant_htons(ETH_P_IPV6))
		return encap_ipv6(skb, IPPROTO_IPV6, ETH_P_IPV6);
	else
		return TC_ACT_OK;
}