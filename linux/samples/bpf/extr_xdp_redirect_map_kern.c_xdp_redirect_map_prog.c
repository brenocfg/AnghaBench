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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct xdp_md {scalar_t__ data; scalar_t__ data_end; } ;
struct ethhdr {int dummy; } ;

/* Variables and functions */
 int XDP_DROP ; 
 long* bpf_map_lookup_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bpf_redirect_map (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxcnt ; 
 int /*<<< orphan*/  swap_src_dst_mac (void*) ; 
 int /*<<< orphan*/  tx_port ; 

int xdp_redirect_map_prog(struct xdp_md *ctx)
{
	void *data_end = (void *)(long)ctx->data_end;
	void *data = (void *)(long)ctx->data;
	struct ethhdr *eth = data;
	int rc = XDP_DROP;
	int vport, port = 0, m = 0;
	long *value;
	u32 key = 0;
	u64 nh_off;

	nh_off = sizeof(*eth);
	if (data + nh_off > data_end)
		return rc;

	/* constant virtual port */
	vport = 0;

	/* count packet in global counter */
	value = bpf_map_lookup_elem(&rxcnt, &key);
	if (value)
		*value += 1;

	swap_src_dst_mac(data);

	/* send packet out physical port */
	return bpf_redirect_map(&tx_port, vport, 0);
}