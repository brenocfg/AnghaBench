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
struct aio_kiocb {TYPE_1__* ki_ctx; int /*<<< orphan*/  ki_refcnt; } ;
struct TYPE_2__ {int /*<<< orphan*/  reqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  kiocb_cachep ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct aio_kiocb*) ; 
 int /*<<< orphan*/  percpu_ref_put (int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void iocb_put(struct aio_kiocb *iocb)
{
	if (refcount_read(&iocb->ki_refcnt) == 0 ||
	    refcount_dec_and_test(&iocb->ki_refcnt)) {
		percpu_ref_put(&iocb->ki_ctx->reqs);
		kmem_cache_free(kiocb_cachep, iocb);
	}
}