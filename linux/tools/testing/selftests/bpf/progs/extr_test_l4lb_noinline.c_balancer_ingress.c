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
struct eth_hdr {int eth_proto; } ;
struct __sk_buff {scalar_t__ data; scalar_t__ data_end; } ;
typedef  int __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int TC_ACT_SHOT ; 
 int bpf_htons (int /*<<< orphan*/ ) ; 
 int process_packet (void*,int,void*,int,struct __sk_buff*) ; 

int balancer_ingress(struct __sk_buff *ctx)
{
	void *data_end = (void *)(long)ctx->data_end;
	void *data = (void *)(long)ctx->data;
	struct eth_hdr *eth = data;
	__u32 eth_proto;
	__u32 nh_off;

	nh_off = sizeof(struct eth_hdr);
	if (data + nh_off > data_end)
		return TC_ACT_SHOT;
	eth_proto = eth->eth_proto;
	if (eth_proto == bpf_htons(ETH_P_IP))
		return process_packet(data, nh_off, data_end, false, ctx);
	else if (eth_proto == bpf_htons(ETH_P_IPV6))
		return process_packet(data, nh_off, data_end, true, ctx);
	else
		return TC_ACT_SHOT;
}