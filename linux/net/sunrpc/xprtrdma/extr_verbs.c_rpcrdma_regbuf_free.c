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
struct rpcrdma_regbuf {struct rpcrdma_regbuf* rg_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct rpcrdma_regbuf*) ; 
 int /*<<< orphan*/  rpcrdma_regbuf_dma_unmap (struct rpcrdma_regbuf*) ; 

__attribute__((used)) static void rpcrdma_regbuf_free(struct rpcrdma_regbuf *rb)
{
	rpcrdma_regbuf_dma_unmap(rb);
	if (rb)
		kfree(rb->rg_data);
	kfree(rb);
}