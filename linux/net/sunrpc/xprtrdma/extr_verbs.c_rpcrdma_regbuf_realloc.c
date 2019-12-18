#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t length; } ;
struct rpcrdma_regbuf {TYPE_1__ rg_iov; void* rg_data; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpcrdma_regbuf_dma_unmap (struct rpcrdma_regbuf*) ; 

bool rpcrdma_regbuf_realloc(struct rpcrdma_regbuf *rb, size_t size, gfp_t flags)
{
	void *buf;

	buf = kmalloc(size, flags);
	if (!buf)
		return false;

	rpcrdma_regbuf_dma_unmap(rb);
	kfree(rb->rg_data);

	rb->rg_data = buf;
	rb->rg_iov.length = size;
	return true;
}