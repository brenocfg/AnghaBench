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
struct resv_map {int dummy; } ;
struct inode {long i_blocks; int /*<<< orphan*/  i_lock; } ;
struct hugepage_subpool {int dummy; } ;
struct hstate {int dummy; } ;

/* Variables and functions */
 long blocks_per_huge_page (struct hstate*) ; 
 struct hstate* hstate_inode (struct inode*) ; 
 long hugepage_subpool_put_pages (struct hugepage_subpool*,long) ; 
 int /*<<< orphan*/  hugetlb_acct_memory (struct hstate*,long) ; 
 struct resv_map* inode_resv_map (struct inode*) ; 
 long region_del (struct resv_map*,long,long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct hugepage_subpool* subpool_inode (struct inode*) ; 

long hugetlb_unreserve_pages(struct inode *inode, long start, long end,
								long freed)
{
	struct hstate *h = hstate_inode(inode);
	struct resv_map *resv_map = inode_resv_map(inode);
	long chg = 0;
	struct hugepage_subpool *spool = subpool_inode(inode);
	long gbl_reserve;

	/*
	 * Since this routine can be called in the evict inode path for all
	 * hugetlbfs inodes, resv_map could be NULL.
	 */
	if (resv_map) {
		chg = region_del(resv_map, start, end);
		/*
		 * region_del() can fail in the rare case where a region
		 * must be split and another region descriptor can not be
		 * allocated.  If end == LONG_MAX, it will not fail.
		 */
		if (chg < 0)
			return chg;
	}

	spin_lock(&inode->i_lock);
	inode->i_blocks -= (blocks_per_huge_page(h) * freed);
	spin_unlock(&inode->i_lock);

	/*
	 * If the subpool has a minimum size, the number of global
	 * reservations to be released may be adjusted.
	 */
	gbl_reserve = hugepage_subpool_put_pages(spool, (chg - freed));
	hugetlb_acct_memory(h, -gbl_reserve);

	return 0;
}