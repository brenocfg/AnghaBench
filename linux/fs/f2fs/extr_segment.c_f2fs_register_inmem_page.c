#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct inode {int dummy; } ;
struct inmem_pages {int /*<<< orphan*/  list; struct page* page; } ;
struct TYPE_2__ {int /*<<< orphan*/  inmem_lock; int /*<<< orphan*/  inmem_pages; } ;

/* Variables and functions */
 scalar_t__ ATOMIC_WRITTEN_PAGE ; 
 TYPE_1__* F2FS_I (struct inode*) ; 
 int /*<<< orphan*/  F2FS_INMEM_PAGES ; 
 int /*<<< orphan*/  F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INMEM ; 
 struct inmem_pages* f2fs_kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_set_page_private (struct page*,unsigned long) ; 
 int /*<<< orphan*/  f2fs_trace_pid (struct page*) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  inc_page_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inmem_entry_slab ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_f2fs_register_inmem_page (struct page*,int /*<<< orphan*/ ) ; 

void f2fs_register_inmem_page(struct inode *inode, struct page *page)
{
	struct inmem_pages *new;

	f2fs_trace_pid(page);

	f2fs_set_page_private(page, (unsigned long)ATOMIC_WRITTEN_PAGE);

	new = f2fs_kmem_cache_alloc(inmem_entry_slab, GFP_NOFS);

	/* add atomic page indices to the list */
	new->page = page;
	INIT_LIST_HEAD(&new->list);

	/* increase reference count with clean state */
	get_page(page);
	mutex_lock(&F2FS_I(inode)->inmem_lock);
	list_add_tail(&new->list, &F2FS_I(inode)->inmem_pages);
	inc_page_count(F2FS_I_SB(inode), F2FS_INMEM_PAGES);
	mutex_unlock(&F2FS_I(inode)->inmem_lock);

	trace_f2fs_register_inmem_page(page, INMEM);
}