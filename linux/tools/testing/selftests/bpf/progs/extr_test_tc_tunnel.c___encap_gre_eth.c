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
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_TEB ; 
 int /*<<< orphan*/  IPPROTO_GRE ; 
 int TC_ACT_OK ; 
 scalar_t__ __bpf_constant_htons (int /*<<< orphan*/ ) ; 
 int encap_ipv4 (struct __sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int __encap_gre_eth(struct __sk_buff *skb)
{
	if (skb->protocol == __bpf_constant_htons(ETH_P_IP))
		return encap_ipv4(skb, IPPROTO_GRE, ETH_P_TEB);
	else
		return TC_ACT_OK;
}