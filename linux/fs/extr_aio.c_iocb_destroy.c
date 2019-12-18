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
struct aio_kiocb {TYPE_1__* ki_ctx; scalar_t__ ki_filp; scalar_t__ ki_eventfd; } ;
struct TYPE_2__ {int /*<<< orphan*/  reqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  eventfd_ctx_put (scalar_t__) ; 
 int /*<<< orphan*/  fput (scalar_t__) ; 
 int /*<<< orphan*/  kiocb_cachep ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct aio_kiocb*) ; 
 int /*<<< orphan*/  percpu_ref_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void iocb_destroy(struct aio_kiocb *iocb)
{
	if (iocb->ki_eventfd)
		eventfd_ctx_put(iocb->ki_eventfd);
	if (iocb->ki_filp)
		fput(iocb->ki_filp);
	percpu_ref_put(&iocb->ki_ctx->reqs);
	kmem_cache_free(kiocb_cachep, iocb);
}