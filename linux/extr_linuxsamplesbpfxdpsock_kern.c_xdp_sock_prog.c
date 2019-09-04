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
struct xdp_md {int rx_queue_index; } ;

/* Variables and functions */
 int XDP_ABORTED ; 
 int XDP_PASS ; 
 int* bpf_map_lookup_elem (int /*<<< orphan*/ *,int*) ; 
 int bpf_redirect_map (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qidconf_map ; 
 int /*<<< orphan*/  xsks_map ; 

int xdp_sock_prog(struct xdp_md *ctx)
{
	int *qidconf, key = 0, idx;
	unsigned int *rr;

	qidconf = bpf_map_lookup_elem(&qidconf_map, &key);
	if (!qidconf)
		return XDP_ABORTED;

	if (*qidconf != ctx->rx_queue_index)
		return XDP_PASS;

#if RR_LB /* NB! RR_LB is configured in xdpsock.h */
	rr = bpf_map_lookup_elem(&rr_map, &key);
	if (!rr)
		return XDP_ABORTED;

	*rr = (*rr + 1) & (MAX_SOCKS - 1);
	idx = *rr;
#else
	idx = 0;
#endif

	return bpf_redirect_map(&xsks_map, idx, 0);
}