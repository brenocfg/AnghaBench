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
struct queue_pages {unsigned long flags; int /*<<< orphan*/  pagelist; } ;
struct page {int dummy; } ;
struct mm_walk {int /*<<< orphan*/  vma; struct queue_pages* private; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int EIO ; 
 unsigned long MPOL_MF_MOVE ; 
 unsigned long MPOL_MF_MOVE_ALL ; 
 int /*<<< orphan*/  __split_huge_pmd (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long,int,int /*<<< orphan*/ *) ; 
 scalar_t__ is_huge_zero_page (struct page*) ; 
 int /*<<< orphan*/  is_pmd_migration_entry (int /*<<< orphan*/ ) ; 
 scalar_t__ migrate_page_add (struct page*,int /*<<< orphan*/ ,unsigned long) ; 
 struct page* pmd_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_pages_required (struct page*,struct queue_pages*) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vma_migratable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int queue_pages_pmd(pmd_t *pmd, spinlock_t *ptl, unsigned long addr,
				unsigned long end, struct mm_walk *walk)
{
	int ret = 0;
	struct page *page;
	struct queue_pages *qp = walk->private;
	unsigned long flags;

	if (unlikely(is_pmd_migration_entry(*pmd))) {
		ret = -EIO;
		goto unlock;
	}
	page = pmd_page(*pmd);
	if (is_huge_zero_page(page)) {
		spin_unlock(ptl);
		__split_huge_pmd(walk->vma, pmd, addr, false, NULL);
		ret = 2;
		goto out;
	}
	if (!queue_pages_required(page, qp))
		goto unlock;

	flags = qp->flags;
	/* go to thp migration */
	if (flags & (MPOL_MF_MOVE | MPOL_MF_MOVE_ALL)) {
		if (!vma_migratable(walk->vma) ||
		    migrate_page_add(page, qp->pagelist, flags)) {
			ret = 1;
			goto unlock;
		}
	} else
		ret = -EIO;
unlock:
	spin_unlock(ptl);
out:
	return ret;
}