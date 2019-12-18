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
struct xdp_frame {struct net_device* dev_rx; } ;
struct xdp_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct bpf_cpu_map_entry {int dummy; } ;

/* Variables and functions */
 int EOVERFLOW ; 
 int /*<<< orphan*/  bq_enqueue (struct bpf_cpu_map_entry*,struct xdp_frame*) ; 
 struct xdp_frame* convert_to_xdp_frame (struct xdp_buff*) ; 
 scalar_t__ unlikely (int) ; 

int cpu_map_enqueue(struct bpf_cpu_map_entry *rcpu, struct xdp_buff *xdp,
		    struct net_device *dev_rx)
{
	struct xdp_frame *xdpf;

	xdpf = convert_to_xdp_frame(xdp);
	if (unlikely(!xdpf))
		return -EOVERFLOW;

	/* Info needed when constructing SKB on remote CPU */
	xdpf->dev_rx = dev_rx;

	bq_enqueue(rcpu, xdpf);
	return 0;
}