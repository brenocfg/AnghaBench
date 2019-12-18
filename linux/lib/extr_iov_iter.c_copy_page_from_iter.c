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
struct page {int dummy; } ;
struct iov_iter {int type; } ;

/* Variables and functions */
 int ITER_BVEC ; 
 int ITER_KVEC ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 size_t _copy_from_iter (void*,size_t,struct iov_iter*) ; 
 size_t copy_page_from_iter_iovec (struct page*,size_t,size_t,struct iov_iter*) ; 
 scalar_t__ iov_iter_is_discard (struct iov_iter*) ; 
 scalar_t__ iov_iter_is_pipe (struct iov_iter*) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  page_copy_sane (struct page*,size_t,size_t) ; 
 scalar_t__ unlikely (int) ; 

size_t copy_page_from_iter(struct page *page, size_t offset, size_t bytes,
			 struct iov_iter *i)
{
	if (unlikely(!page_copy_sane(page, offset, bytes)))
		return 0;
	if (unlikely(iov_iter_is_pipe(i) || iov_iter_is_discard(i))) {
		WARN_ON(1);
		return 0;
	}
	if (i->type & (ITER_BVEC|ITER_KVEC)) {
		void *kaddr = kmap_atomic(page);
		size_t wanted = _copy_from_iter(kaddr + offset, bytes, i);
		kunmap_atomic(kaddr);
		return wanted;
	} else
		return copy_page_from_iter_iovec(page, offset, bytes, i);
}