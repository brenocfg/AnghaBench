#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lkey; int /*<<< orphan*/  addr; } ;
struct rpcrdma_regbuf {scalar_t__ rg_direction; TYPE_2__ rg_iov; struct ib_device* rg_device; scalar_t__ rg_base; } ;
struct rpcrdma_ia {TYPE_1__* ri_pd; struct ib_device* ri_device; } ;
struct ib_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  local_dma_lkey; } ;

/* Variables and functions */
 scalar_t__ DMA_NONE ; 
 int /*<<< orphan*/  ib_dma_map_single (struct ib_device*,void*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ib_dma_mapping_error (struct ib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdmab_addr (struct rpcrdma_regbuf*) ; 
 int /*<<< orphan*/  rdmab_length (struct rpcrdma_regbuf*) ; 

bool
__rpcrdma_dma_map_regbuf(struct rpcrdma_ia *ia, struct rpcrdma_regbuf *rb)
{
	struct ib_device *device = ia->ri_device;

	if (rb->rg_direction == DMA_NONE)
		return false;

	rb->rg_iov.addr = ib_dma_map_single(device,
					    (void *)rb->rg_base,
					    rdmab_length(rb),
					    rb->rg_direction);
	if (ib_dma_mapping_error(device, rdmab_addr(rb)))
		return false;

	rb->rg_device = device;
	rb->rg_iov.lkey = ia->ri_pd->local_dma_lkey;
	return true;
}