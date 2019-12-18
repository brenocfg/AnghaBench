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
struct hugepage_subpool {int max_hpages; long used_hpages; int min_hpages; long rsv_hpages; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_or_release_subpool (struct hugepage_subpool*) ; 

__attribute__((used)) static long hugepage_subpool_put_pages(struct hugepage_subpool *spool,
				       long delta)
{
	long ret = delta;

	if (!spool)
		return delta;

	spin_lock(&spool->lock);

	if (spool->max_hpages != -1)		/* maximum size accounting */
		spool->used_hpages -= delta;

	 /* minimum size accounting */
	if (spool->min_hpages != -1 && spool->used_hpages < spool->min_hpages) {
		if (spool->rsv_hpages + delta <= spool->min_hpages)
			ret = 0;
		else
			ret = spool->rsv_hpages + delta - spool->min_hpages;

		spool->rsv_hpages += delta;
		if (spool->rsv_hpages > spool->min_hpages)
			spool->rsv_hpages = spool->min_hpages;
	}

	/*
	 * If hugetlbfs_put_super couldn't free spool due to an outstanding
	 * quota reference, free it now.
	 */
	unlock_or_release_subpool(spool);

	return ret;
}