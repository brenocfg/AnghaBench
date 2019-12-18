#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iov_iter {size_t count; } ;
struct TYPE_3__ {size_t iov_len; size_t bv_len; scalar_t__ iov_base; scalar_t__ bv_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ iov_iter_is_discard (struct iov_iter const*) ; 
 scalar_t__ iov_iter_is_pipe (struct iov_iter const*) ; 
 int /*<<< orphan*/  iterate_all_kinds (struct iov_iter const*,size_t,TYPE_1__,unsigned long,unsigned long,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 TYPE_1__ v ; 

unsigned long iov_iter_gap_alignment(const struct iov_iter *i)
{
	unsigned long res = 0;
	size_t size = i->count;

	if (unlikely(iov_iter_is_pipe(i) || iov_iter_is_discard(i))) {
		WARN_ON(1);
		return ~0U;
	}

	iterate_all_kinds(i, size, v,
		(res |= (!res ? 0 : (unsigned long)v.iov_base) |
			(size != v.iov_len ? size : 0), 0),
		(res |= (!res ? 0 : (unsigned long)v.bv_offset) |
			(size != v.bv_len ? size : 0)),
		(res |= (!res ? 0 : (unsigned long)v.iov_base) |
			(size != v.iov_len ? size : 0))
		);
	return res;
}