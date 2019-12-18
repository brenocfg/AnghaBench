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
 int TC_ACT_OK ; 
 scalar_t__ bpf_htons (int /*<<< orphan*/ ) ; 
 int handle_ipv4 (struct __sk_buff*) ; 

int tc_prog(struct __sk_buff *skb)
{
	if (skb->protocol == bpf_htons(ETH_P_IP))
		return handle_ipv4(skb);

	return TC_ACT_OK;
}