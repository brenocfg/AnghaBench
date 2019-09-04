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
typedef  int u32 ;
struct xdp_md {scalar_t__ data; scalar_t__ data_end; } ;
struct ethhdr {int dummy; } ;

/* Variables and functions */
 int XDP_DROP ; 
 void* bpf_map_lookup_elem (int /*<<< orphan*/ *,int*) ; 
 int bpf_redirect (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxcnt ; 
 int /*<<< orphan*/  swap_src_dst_mac (void*) ; 
 int /*<<< orphan*/  tx_port ; 

int xdp_redirect_prog(struct xdp_md *ctx)
{
	void *data_end = (void *)(long)ctx->data_end;
	void *data = (void *)(long)ctx->data;
	struct ethhdr *eth = data;
	int rc = XDP_DROP;
	int *ifindex, port = 0;
	long *value;
	u32 key = 0;
	u64 nh_off;

	nh_off = sizeof(*eth);
	if (data + nh_off > data_end)
		return rc;

	ifindex = bpf_map_lookup_elem(&tx_port, &port);
	if (!ifindex)
		return rc;

	value = bpf_map_lookup_elem(&rxcnt, &key);
	if (value)
		*value += 1;

	swap_src_dst_mac(data);
	return bpf_redirect(*ifindex, 0);
}