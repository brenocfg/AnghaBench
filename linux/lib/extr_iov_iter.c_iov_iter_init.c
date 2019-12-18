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
struct kvec {int dummy; } ;
struct iovec {int dummy; } ;
struct iov_iter {unsigned int type; unsigned long nr_segs; size_t count; scalar_t__ iov_offset; struct iovec const* iov; struct kvec* kvec; } ;

/* Variables and functions */
 unsigned int ITER_IOVEC ; 
 unsigned int ITER_KVEC ; 
 unsigned int READ ; 
 int /*<<< orphan*/  WARN_ON (unsigned int) ; 
 unsigned int WRITE ; 
 scalar_t__ uaccess_kernel () ; 

void iov_iter_init(struct iov_iter *i, unsigned int direction,
			const struct iovec *iov, unsigned long nr_segs,
			size_t count)
{
	WARN_ON(direction & ~(READ | WRITE));
	direction &= READ | WRITE;

	/* It will get better.  Eventually... */
	if (uaccess_kernel()) {
		i->type = ITER_KVEC | direction;
		i->kvec = (struct kvec *)iov;
	} else {
		i->type = ITER_IOVEC | direction;
		i->iov = iov;
	}
	i->nr_segs = nr_segs;
	i->iov_offset = 0;
	i->count = count;
}