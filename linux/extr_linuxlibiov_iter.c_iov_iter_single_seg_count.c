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
struct iov_iter {int type; size_t count; int nr_segs; scalar_t__ iov_offset; TYPE_1__* iov; TYPE_2__* bvec; } ;
struct TYPE_4__ {scalar_t__ bv_len; } ;
struct TYPE_3__ {scalar_t__ iov_len; } ;

/* Variables and functions */
 int ITER_BVEC ; 
 int ITER_PIPE ; 
 size_t min (size_t,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

size_t iov_iter_single_seg_count(const struct iov_iter *i)
{
	if (unlikely(i->type & ITER_PIPE))
		return i->count;	// it is a silly place, anyway
	if (i->nr_segs == 1)
		return i->count;
	else if (i->type & ITER_BVEC)
		return min(i->count, i->bvec->bv_len - i->iov_offset);
	else
		return min(i->count, i->iov->iov_len - i->iov_offset);
}