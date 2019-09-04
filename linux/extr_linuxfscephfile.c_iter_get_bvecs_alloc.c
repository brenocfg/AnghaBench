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
struct iov_iter {int dummy; } ;
struct bio_vec {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  INT_MAX ; 
 int __GFP_ZERO ; 
 scalar_t__ __iter_get_bvecs (struct iov_iter*,size_t,struct bio_vec*) ; 
 size_t iov_iter_count (struct iov_iter*) ; 
 int iov_iter_npages (struct iov_iter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iov_iter_reexpand (struct iov_iter*,size_t) ; 
 int /*<<< orphan*/  iov_iter_truncate (struct iov_iter*,size_t) ; 
 int /*<<< orphan*/  kvfree (struct bio_vec*) ; 
 struct bio_vec* kvmalloc_array (int,int,int) ; 

__attribute__((used)) static ssize_t iter_get_bvecs_alloc(struct iov_iter *iter, size_t maxsize,
				    struct bio_vec **bvecs, int *num_bvecs)
{
	struct bio_vec *bv;
	size_t orig_count = iov_iter_count(iter);
	ssize_t bytes;
	int npages;

	iov_iter_truncate(iter, maxsize);
	npages = iov_iter_npages(iter, INT_MAX);
	iov_iter_reexpand(iter, orig_count);

	/*
	 * __iter_get_bvecs() may populate only part of the array -- zero it
	 * out.
	 */
	bv = kvmalloc_array(npages, sizeof(*bv), GFP_KERNEL | __GFP_ZERO);
	if (!bv)
		return -ENOMEM;

	bytes = __iter_get_bvecs(iter, maxsize, bv);
	if (bytes < 0) {
		/*
		 * No pages were pinned -- just free the array.
		 */
		kvfree(bv);
		return bytes;
	}

	*bvecs = bv;
	*num_bvecs = npages;
	return bytes;
}