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
struct parse_pkt {scalar_t__ vlan_outer; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 scalar_t__ TESTVLAN ; 
 int XDP_ABORTED ; 
 int XDP_PASS ; 
 int /*<<< orphan*/  parse_eth_frame (void*,void*,struct parse_pkt*) ; 

int  xdp_prognum0(struct xdp_md *ctx)
{
	void *data_end = (void *)(long)ctx->data_end;
	void *data     = (void *)(long)ctx->data;
	struct parse_pkt pkt = { 0 };

	if (!parse_eth_frame(data, data_end, &pkt))
		return XDP_ABORTED;

	/* Drop specific VLAN ID example */
	if (pkt.vlan_outer == TESTVLAN)
		return XDP_ABORTED;
	/*
	 * Using XDP_ABORTED makes it possible to record this event,
	 * via tracepoint xdp:xdp_exception like:
	 *  # perf record -a -e xdp:xdp_exception
	 *  # perf script
	 */
	return XDP_PASS;
}