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
struct ipv6hdr {scalar_t__ nexthdr; } ;
struct eth_hdr {scalar_t__ h_proto; } ;
struct __sk_buff {scalar_t__ data_end; scalar_t__ data; } ;
typedef  int /*<<< orphan*/  reject_msg ;
typedef  int /*<<< orphan*/  pass_msg ;
typedef  int /*<<< orphan*/  dont_care_msg ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 scalar_t__ IPPROTO_ICMPV6 ; 
 int TC_ACT_OK ; 
 int TC_ACT_SHOT ; 
 int bpf_skb_under_cgroup (struct __sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_trace_printk (char*,int,...) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_cgrp2_array_pin ; 

int handle_egress(struct __sk_buff *skb)
{
	void *data = (void *)(long)skb->data;
	struct eth_hdr *eth = data;
	struct ipv6hdr *ip6h = data + sizeof(*eth);
	void *data_end = (void *)(long)skb->data_end;
	char dont_care_msg[] = "dont care %04x %d\n";
	char pass_msg[] = "pass\n";
	char reject_msg[] = "reject\n";

	/* single length check */
	if (data + sizeof(*eth) + sizeof(*ip6h) > data_end)
		return TC_ACT_OK;

	if (eth->h_proto != htons(ETH_P_IPV6) ||
	    ip6h->nexthdr != IPPROTO_ICMPV6) {
		bpf_trace_printk(dont_care_msg, sizeof(dont_care_msg),
				 eth->h_proto, ip6h->nexthdr);
		return TC_ACT_OK;
	} else if (bpf_skb_under_cgroup(skb, &test_cgrp2_array_pin, 0) != 1) {
		bpf_trace_printk(pass_msg, sizeof(pass_msg));
		return TC_ACT_OK;
	} else {
		bpf_trace_printk(reject_msg, sizeof(reject_msg));
		return TC_ACT_SHOT;
	}
}