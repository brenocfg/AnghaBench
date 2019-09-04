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
struct hugepage_subpool {int count; long max_hpages; long min_hpages; long rsv_hpages; struct hstate* hstate; int /*<<< orphan*/  lock; } ;
struct hstate {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ hugetlb_acct_memory (struct hstate*,long) ; 
 int /*<<< orphan*/  kfree (struct hugepage_subpool*) ; 
 struct hugepage_subpool* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct hugepage_subpool *hugepage_new_subpool(struct hstate *h, long max_hpages,
						long min_hpages)
{
	struct hugepage_subpool *spool;

	spool = kzalloc(sizeof(*spool), GFP_KERNEL);
	if (!spool)
		return NULL;

	spin_lock_init(&spool->lock);
	spool->count = 1;
	spool->max_hpages = max_hpages;
	spool->hstate = h;
	spool->min_hpages = min_hpages;

	if (min_hpages != -1 && hugetlb_acct_memory(h, min_hpages)) {
		kfree(spool);
		return NULL;
	}
	spool->rsv_hpages = min_hpages;

	return spool;
}