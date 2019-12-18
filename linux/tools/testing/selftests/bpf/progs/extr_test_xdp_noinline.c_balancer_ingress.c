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
struct xdp_md {scalar_t__ data_end; scalar_t__ data; } ;
struct eth_hdr {int /*<<< orphan*/  eth_proto; } ;
typedef  int __u32 ;

/* Variables and functions */
 int ETH_P_IP ; 
 int ETH_P_IPV6 ; 
 int XDP_DROP ; 
 int bpf_ntohs (int /*<<< orphan*/ ) ; 
 int process_packet (void*,int,void*,int,struct xdp_md*) ; 

__attribute__ ((section("xdp-test"), used))
int balancer_ingress(struct xdp_md *ctx)
{
	void *data = (void *)(long)ctx->data;
	void *data_end = (void *)(long)ctx->data_end;
	struct eth_hdr *eth = data;
	__u32 eth_proto;
	__u32 nh_off;

	nh_off = sizeof(struct eth_hdr);
	if (data + nh_off > data_end)
		return XDP_DROP;
	eth_proto = bpf_ntohs(eth->eth_proto);
	if (eth_proto == ETH_P_IP)
		return process_packet(data, nh_off, data_end, 0, ctx);
	else if (eth_proto == ETH_P_IPV6)
		return process_packet(data, nh_off, data_end, 1, ctx);
	else
		return XDP_DROP;
}