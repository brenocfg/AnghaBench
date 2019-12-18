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
struct parse_pkt {scalar_t__ vlan_outer; int vlan_outer_offset; int /*<<< orphan*/  member_0; } ;
struct _vlan_hdr {int /*<<< orphan*/  h_vlan_TCI; } ;

/* Variables and functions */
 scalar_t__ TESTVLAN ; 
 int TO_VLAN ; 
 int XDP_ABORTED ; 
 int XDP_PASS ; 
 int /*<<< orphan*/  bpf_htons (int) ; 
 int bpf_ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_eth_frame (void*,void*,struct parse_pkt*) ; 

int  xdp_prognum1(struct xdp_md *ctx)
{
	void *data_end = (void *)(long)ctx->data_end;
	void *data     = (void *)(long)ctx->data;
	struct parse_pkt pkt = { 0 };

	if (!parse_eth_frame(data, data_end, &pkt))
		return XDP_ABORTED;

	/* Change specific VLAN ID */
	if (pkt.vlan_outer == TESTVLAN) {
		struct _vlan_hdr *vlan_hdr = data + pkt.vlan_outer_offset;

		/* Modifying VLAN, preserve top 4 bits */
		vlan_hdr->h_vlan_TCI =
			bpf_htons((bpf_ntohs(vlan_hdr->h_vlan_TCI) & 0xf000)
				  | TO_VLAN);
	}

	return XDP_PASS;
}