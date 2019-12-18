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
struct page {int /*<<< orphan*/  index; struct address_space* mapping; } ;
struct afs_vnode {int /*<<< orphan*/  cache; } ;
struct address_space {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 struct afs_vnode* AFS_FS_I (int /*<<< orphan*/ ) ; 
 unsigned long AFS_PRIV_MAX ; 
 unsigned long AFS_PRIV_SHIFT ; 
 int /*<<< orphan*/  ClearPagePrivate (struct page*) ; 
 unsigned int PAGE_SIZE ; 
 scalar_t__ PageFsCache (struct page*) ; 
 scalar_t__ PagePrivate (struct page*) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ) ; 
 int afs_store_data (struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 scalar_t__ clear_page_dirty_for_io (struct page*) ; 
 int /*<<< orphan*/  fscache_uncache_page (int /*<<< orphan*/ ,struct page*) ; 
 int /*<<< orphan*/  fscache_wait_on_page_write (int /*<<< orphan*/ ,struct page*) ; 
 unsigned long page_private (struct page*) ; 
 int /*<<< orphan*/  set_page_private (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_afs_page_dirty (struct afs_vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tracepoint_string (char*) ; 

int afs_launder_page(struct page *page)
{
	struct address_space *mapping = page->mapping;
	struct afs_vnode *vnode = AFS_FS_I(mapping->host);
	unsigned long priv;
	unsigned int f, t;
	int ret = 0;

	_enter("{%lx}", page->index);

	priv = page_private(page);
	if (clear_page_dirty_for_io(page)) {
		f = 0;
		t = PAGE_SIZE;
		if (PagePrivate(page)) {
			f = priv & AFS_PRIV_MAX;
			t = priv >> AFS_PRIV_SHIFT;
		}

		trace_afs_page_dirty(vnode, tracepoint_string("launder"),
				     page->index, priv);
		ret = afs_store_data(mapping, page->index, page->index, t, f);
	}

	trace_afs_page_dirty(vnode, tracepoint_string("laundered"),
			     page->index, priv);
	set_page_private(page, 0);
	ClearPagePrivate(page);

#ifdef CONFIG_AFS_FSCACHE
	if (PageFsCache(page)) {
		fscache_wait_on_page_write(vnode->cache, page);
		fscache_uncache_page(vnode->cache, page);
	}
#endif
	return ret;
}