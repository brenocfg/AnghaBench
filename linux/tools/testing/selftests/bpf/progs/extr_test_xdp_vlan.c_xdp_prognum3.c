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
struct parse_pkt {scalar_t__ vlan_outer_offset; int /*<<< orphan*/  member_0; } ;
struct ethhdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLAN_HDR_SZ ; 
 int XDP_ABORTED ; 
 int XDP_PASS ; 
 int /*<<< orphan*/  bpf_xdp_adjust_head (struct xdp_md*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_eth_frame (struct ethhdr*,void*,struct parse_pkt*) ; 
 int /*<<< orphan*/  shift_mac_4bytes_32bit (void*) ; 

int  xdp_prognum3(struct xdp_md *ctx)
{
	void *data_end = (void *)(long)ctx->data_end;
	void *data     = (void *)(long)ctx->data;
	struct ethhdr *orig_eth = data;
	struct parse_pkt pkt = { 0 };

	if (!parse_eth_frame(orig_eth, data_end, &pkt))
		return XDP_ABORTED;

	/* Skip packet if no outer VLAN was detected */
	if (pkt.vlan_outer_offset == 0)
		return XDP_PASS;

	/* Simply shift down MAC addrs 4 bytes, overwrite h_proto + TCI */
	shift_mac_4bytes_32bit(data);

	/* Move start of packet header seen by Linux kernel stack */
	bpf_xdp_adjust_head(ctx, VLAN_HDR_SZ);

	return XDP_PASS;
}