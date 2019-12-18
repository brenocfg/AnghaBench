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
struct rpcrdma_regbuf {int /*<<< orphan*/ * rg_device; int /*<<< orphan*/  rg_direction; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdmab_addr (struct rpcrdma_regbuf*) ; 
 int /*<<< orphan*/  rdmab_length (struct rpcrdma_regbuf*) ; 
 int /*<<< orphan*/  rpcrdma_regbuf_is_mapped (struct rpcrdma_regbuf*) ; 

__attribute__((used)) static void rpcrdma_regbuf_dma_unmap(struct rpcrdma_regbuf *rb)
{
	if (!rb)
		return;

	if (!rpcrdma_regbuf_is_mapped(rb))
		return;

	ib_dma_unmap_single(rb->rg_device, rdmab_addr(rb), rdmab_length(rb),
			    rb->rg_direction);
	rb->rg_device = NULL;
}