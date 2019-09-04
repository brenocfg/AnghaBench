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
struct page {int dummy; } ;
struct inode {int dummy; } ;
struct inmem_pages {int /*<<< orphan*/  list; struct page* page; } ;
struct f2fs_sb_info {int /*<<< orphan*/ * inode_lock; int /*<<< orphan*/ * inode_list; } ;
struct f2fs_inode_info {int /*<<< orphan*/  inmem_lock; int /*<<< orphan*/  inmem_ilist; int /*<<< orphan*/  inmem_pages; } ;

/* Variables and functions */
 size_t ATOMIC_FILE ; 
 scalar_t__ ATOMIC_WRITTEN_PAGE ; 
 struct f2fs_inode_info* F2FS_I (struct inode*) ; 
 int /*<<< orphan*/  F2FS_INMEM_PAGES ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INMEM ; 
 int /*<<< orphan*/  SetPagePrivate (struct page*) ; 
 struct inmem_pages* f2fs_kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_trace_pid (struct page*) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  inc_page_count (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inmem_entry_slab ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_page_private (struct page*,unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_f2fs_register_inmem_page (struct page*,int /*<<< orphan*/ ) ; 

void f2fs_register_inmem_page(struct inode *inode, struct page *page)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	struct f2fs_inode_info *fi = F2FS_I(inode);
	struct inmem_pages *new;

	f2fs_trace_pid(page);

	set_page_private(page, (unsigned long)ATOMIC_WRITTEN_PAGE);
	SetPagePrivate(page);

	new = f2fs_kmem_cache_alloc(inmem_entry_slab, GFP_NOFS);

	/* add atomic page indices to the list */
	new->page = page;
	INIT_LIST_HEAD(&new->list);

	/* increase reference count with clean state */
	mutex_lock(&fi->inmem_lock);
	get_page(page);
	list_add_tail(&new->list, &fi->inmem_pages);
	spin_lock(&sbi->inode_lock[ATOMIC_FILE]);
	if (list_empty(&fi->inmem_ilist))
		list_add_tail(&fi->inmem_ilist, &sbi->inode_list[ATOMIC_FILE]);
	spin_unlock(&sbi->inode_lock[ATOMIC_FILE]);
	inc_page_count(F2FS_I_SB(inode), F2FS_INMEM_PAGES);
	mutex_unlock(&fi->inmem_lock);

	trace_f2fs_register_inmem_page(page, INMEM);
}