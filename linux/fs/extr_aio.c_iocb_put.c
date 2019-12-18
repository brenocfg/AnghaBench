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
struct aio_kiocb {int /*<<< orphan*/  ki_refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  aio_complete (struct aio_kiocb*) ; 
 int /*<<< orphan*/  iocb_destroy (struct aio_kiocb*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void iocb_put(struct aio_kiocb *iocb)
{
	if (refcount_dec_and_test(&iocb->ki_refcnt)) {
		aio_complete(iocb);
		iocb_destroy(iocb);
	}
}