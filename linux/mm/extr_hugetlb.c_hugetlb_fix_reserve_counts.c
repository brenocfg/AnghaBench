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
struct inode {int dummy; } ;
struct hugepage_subpool {int dummy; } ;
struct hstate {int dummy; } ;

/* Variables and functions */
 struct hstate* hstate_inode (struct inode*) ; 
 long hugepage_subpool_get_pages (struct hugepage_subpool*,int) ; 
 int /*<<< orphan*/  hugetlb_acct_memory (struct hstate*,int) ; 
 struct hugepage_subpool* subpool_inode (struct inode*) ; 

void hugetlb_fix_reserve_counts(struct inode *inode)
{
	struct hugepage_subpool *spool = subpool_inode(inode);
	long rsv_adjust;

	rsv_adjust = hugepage_subpool_get_pages(spool, 1);
	if (rsv_adjust) {
		struct hstate *h = hstate_inode(inode);

		hugetlb_acct_memory(h, 1);
	}
}