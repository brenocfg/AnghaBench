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
struct __sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int TC_ACT_OK ; 
 int /*<<< orphan*/  TESTVLAN ; 
 int /*<<< orphan*/  bpf_htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_skb_vlan_push (struct __sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int _tc_progA(struct __sk_buff *ctx)
{
	bpf_skb_vlan_push(ctx, bpf_htons(ETH_P_8021Q), TESTVLAN);

	return TC_ACT_OK;
}