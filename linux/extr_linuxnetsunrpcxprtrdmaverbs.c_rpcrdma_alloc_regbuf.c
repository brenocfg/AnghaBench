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
struct rpcrdma_regbuf {int rg_direction; TYPE_1__ rg_iov; int /*<<< orphan*/ * rg_device; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct rpcrdma_regbuf* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct rpcrdma_regbuf* kmalloc (int,int /*<<< orphan*/ ) ; 

struct rpcrdma_regbuf *
rpcrdma_alloc_regbuf(size_t size, enum dma_data_direction direction,
		     gfp_t flags)
{
	struct rpcrdma_regbuf *rb;

	rb = kmalloc(sizeof(*rb) + size, flags);
	if (rb == NULL)
		return ERR_PTR(-ENOMEM);

	rb->rg_device = NULL;
	rb->rg_direction = direction;
	rb->rg_iov.length = size;

	return rb;
}