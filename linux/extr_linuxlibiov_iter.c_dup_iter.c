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
struct iovec {int dummy; } ;
struct iov_iter {int type; void const* bvec; int nr_segs; void const* iov; } ;
struct bio_vec {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ITER_BVEC ; 
 int ITER_PIPE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 void* kmemdup (void const*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

const void *dup_iter(struct iov_iter *new, struct iov_iter *old, gfp_t flags)
{
	*new = *old;
	if (unlikely(new->type & ITER_PIPE)) {
		WARN_ON(1);
		return NULL;
	}
	if (new->type & ITER_BVEC)
		return new->bvec = kmemdup(new->bvec,
				    new->nr_segs * sizeof(struct bio_vec),
				    flags);
	else
		/* iovec and kvec have identical layout */
		return new->iov = kmemdup(new->iov,
				   new->nr_segs * sizeof(struct iovec),
				   flags);
}