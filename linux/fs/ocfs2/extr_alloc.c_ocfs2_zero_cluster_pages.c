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
typedef  int /*<<< orphan*/  u64 ;
struct super_block {int dummy; } ;
struct page {int index; } ;
struct inode {struct super_block* i_sb; } ;
typedef  int loff_t ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  OCFS2_SB (struct super_block*) ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  ocfs2_map_and_dirty_page (struct inode*,int /*<<< orphan*/ *,unsigned int,unsigned int,struct page*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_sparse_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_unlock_and_free_pages (struct page**,int) ; 

__attribute__((used)) static void ocfs2_zero_cluster_pages(struct inode *inode, loff_t start,
				     loff_t end, struct page **pages,
				     int numpages, u64 phys, handle_t *handle)
{
	int i;
	struct page *page;
	unsigned int from, to = PAGE_SIZE;
	struct super_block *sb = inode->i_sb;

	BUG_ON(!ocfs2_sparse_alloc(OCFS2_SB(sb)));

	if (numpages == 0)
		goto out;

	to = PAGE_SIZE;
	for(i = 0; i < numpages; i++) {
		page = pages[i];

		from = start & (PAGE_SIZE - 1);
		if ((end >> PAGE_SHIFT) == page->index)
			to = end & (PAGE_SIZE - 1);

		BUG_ON(from > PAGE_SIZE);
		BUG_ON(to > PAGE_SIZE);

		ocfs2_map_and_dirty_page(inode, handle, from, to, page, 1,
					 &phys);

		start = (page->index + 1) << PAGE_SHIFT;
	}
out:
	if (pages)
		ocfs2_unlock_and_free_pages(pages, numpages);
}