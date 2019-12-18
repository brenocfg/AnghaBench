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
struct page {scalar_t__ index; } ;
struct inode {int dummy; } ;
struct address_space {struct inode* host; } ;
typedef  scalar_t__ pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  hugetlb_fix_reserve_counts (struct inode*) ; 
 int /*<<< orphan*/  hugetlb_unreserve_pages (struct inode*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  remove_huge_page (struct page*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hugetlbfs_error_remove_page(struct address_space *mapping,
				struct page *page)
{
	struct inode *inode = mapping->host;
	pgoff_t index = page->index;

	remove_huge_page(page);
	if (unlikely(hugetlb_unreserve_pages(inode, index, index + 1, 1)))
		hugetlb_fix_reserve_counts(inode);

	return 0;
}