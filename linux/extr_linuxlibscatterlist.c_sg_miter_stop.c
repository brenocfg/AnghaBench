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
struct sg_mapping_iter {scalar_t__ consumed; scalar_t__ length; int __flags; int /*<<< orphan*/ * addr; int /*<<< orphan*/ * page; int /*<<< orphan*/  __remaining; int /*<<< orphan*/  __offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  PageSlab (int /*<<< orphan*/ *) ; 
 int SG_MITER_ATOMIC ; 
 int SG_MITER_TO_SG ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_kernel_dcache_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kunmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kunmap_atomic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  preemptible () ; 

void sg_miter_stop(struct sg_mapping_iter *miter)
{
	WARN_ON(miter->consumed > miter->length);

	/* drop resources from the last iteration */
	if (miter->addr) {
		miter->__offset += miter->consumed;
		miter->__remaining -= miter->consumed;

		if ((miter->__flags & SG_MITER_TO_SG) &&
		    !PageSlab(miter->page))
			flush_kernel_dcache_page(miter->page);

		if (miter->__flags & SG_MITER_ATOMIC) {
			WARN_ON_ONCE(preemptible());
			kunmap_atomic(miter->addr);
		} else
			kunmap(miter->page);

		miter->page = NULL;
		miter->addr = NULL;
		miter->length = 0;
		miter->consumed = 0;
	}
}