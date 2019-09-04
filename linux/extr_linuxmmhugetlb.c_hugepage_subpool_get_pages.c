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
 long ENOMEM ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long hugepage_subpool_get_pages(struct hugepage_subpool *spool,
				      long delta)
{
	long ret = delta;

	if (!spool)
		return ret;

	spin_lock(&spool->lock);

	if (spool->max_hpages != -1) {		/* maximum size accounting */
		if ((spool->used_hpages + delta) <= spool->max_hpages)
			spool->used_hpages += delta;
		else {
			ret = -ENOMEM;
			goto unlock_ret;
		}
	}

	/* minimum size accounting */
	if (spool->min_hpages != -1 && spool->rsv_hpages) {
		if (delta > spool->rsv_hpages) {
			/*
			 * Asking for more reserves than those already taken on
			 * behalf of subpool.  Return difference.
			 */
			ret = delta - spool->rsv_hpages;
			spool->rsv_hpages = 0;
		} else {
			ret = 0;	/* reserves already accounted for */
			spool->rsv_hpages -= delta;
		}
	}

unlock_ret:
	spin_unlock(&spool->lock);
	return ret;
}