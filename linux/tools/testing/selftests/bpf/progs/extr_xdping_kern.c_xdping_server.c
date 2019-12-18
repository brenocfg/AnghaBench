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
struct xdp_md {scalar_t__ data; scalar_t__ data_end; } ;
struct iphdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct icmphdr {scalar_t__ checksum; int /*<<< orphan*/  type; } ;
struct ethhdr {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ICMP_ECHO ; 
 int /*<<< orphan*/  ICMP_ECHOREPLY ; 
 int /*<<< orphan*/  ICMP_ECHO_LEN ; 
 int XDP_TX ; 
 int icmp_check (struct xdp_md*,int /*<<< orphan*/ ) ; 
 scalar_t__ ipv4_csum (struct icmphdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap_src_dst_mac (void*) ; 

int xdping_server(struct xdp_md *ctx)
{
	void *data_end = (void *)(long)ctx->data_end;
	void *data = (void *)(long)ctx->data;
	struct ethhdr *eth = data;
	struct icmphdr *icmph;
	struct iphdr *iph;
	__be32 raddr;
	int ret;

	ret = icmp_check(ctx, ICMP_ECHO);

	if (ret != XDP_TX)
		return ret;

	iph = data + sizeof(*eth);
	icmph = data + sizeof(*eth) + sizeof(*iph);
	raddr = iph->saddr;

	/* Now convert request into echo reply. */
	swap_src_dst_mac(data);
	iph->saddr = iph->daddr;
	iph->daddr = raddr;
	icmph->type = ICMP_ECHOREPLY;
	icmph->checksum = 0;
	icmph->checksum = ipv4_csum(icmph, ICMP_ECHO_LEN);

	return XDP_TX;
}