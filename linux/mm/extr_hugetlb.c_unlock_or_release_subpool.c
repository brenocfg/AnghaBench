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
struct hugepage_subpool {scalar_t__ count; scalar_t__ used_hpages; int min_hpages; int /*<<< orphan*/  hstate; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  hugetlb_acct_memory (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct hugepage_subpool*) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void unlock_or_release_subpool(struct hugepage_subpool *spool)
{
	bool free = (spool->count == 0) && (spool->used_hpages == 0);

	spin_unlock(&spool->lock);

	/* If no pages are used, and no other handles to the subpool
	 * remain, give up any reservations mased on minimum size and
	 * free the subpool */
	if (free) {
		if (spool->min_hpages != -1)
			hugetlb_acct_memory(spool->hstate,
						-spool->min_hpages);
		kfree(spool);
	}
}