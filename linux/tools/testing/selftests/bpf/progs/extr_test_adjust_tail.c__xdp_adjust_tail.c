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

/* Variables and functions */
 int XDP_DROP ; 
 int XDP_TX ; 
 scalar_t__ bpf_xdp_adjust_tail (struct xdp_md*,scalar_t__) ; 

int _xdp_adjust_tail(struct xdp_md *xdp)
{
	void *data_end = (void *)(long)xdp->data_end;
	void *data = (void *)(long)xdp->data;
	int offset = 0;

	if (data_end - data == 54)
		offset = 256;
	else
		offset = 20;
	if (bpf_xdp_adjust_tail(xdp, 0 - offset))
		return XDP_DROP;
	return XDP_TX;
}