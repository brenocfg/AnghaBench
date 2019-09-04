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
struct sg_mapping_iter {int __flags; scalar_t__ __offset; int /*<<< orphan*/  page; scalar_t__ addr; int /*<<< orphan*/  __remaining; int /*<<< orphan*/  length; int /*<<< orphan*/  consumed; int /*<<< orphan*/  piter; } ;

/* Variables and functions */
 int SG_MITER_ATOMIC ; 
 scalar_t__ kmap (int /*<<< orphan*/ ) ; 
 scalar_t__ kmap_atomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_miter_get_next_page (struct sg_mapping_iter*) ; 
 int /*<<< orphan*/  sg_miter_stop (struct sg_mapping_iter*) ; 
 int /*<<< orphan*/  sg_page_iter_page (int /*<<< orphan*/ *) ; 

bool sg_miter_next(struct sg_mapping_iter *miter)
{
	sg_miter_stop(miter);

	/*
	 * Get to the next page if necessary.
	 * __remaining, __offset is adjusted by sg_miter_stop
	 */
	if (!sg_miter_get_next_page(miter))
		return false;

	miter->page = sg_page_iter_page(&miter->piter);
	miter->consumed = miter->length = miter->__remaining;

	if (miter->__flags & SG_MITER_ATOMIC)
		miter->addr = kmap_atomic(miter->page) + miter->__offset;
	else
		miter->addr = kmap(miter->page) + miter->__offset;

	return true;
}