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
struct page {int /*<<< orphan*/  index; TYPE_1__* mapping; } ;
struct afs_vnode {int /*<<< orphan*/  cache; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 struct afs_vnode* AFS_FS_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ClearPagePrivate (struct page*) ; 
 unsigned int PAGE_SIZE ; 
 scalar_t__ PageFsCache (struct page*) ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 scalar_t__ PagePrivate (struct page*) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  fscache_uncache_page (int /*<<< orphan*/ ,struct page*) ; 
 int /*<<< orphan*/  fscache_wait_on_page_write (int /*<<< orphan*/ ,struct page*) ; 
 unsigned long page_private (struct page*) ; 
 int /*<<< orphan*/  set_page_private (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_afs_page_dirty (struct afs_vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tracepoint_string (char*) ; 

__attribute__((used)) static void afs_invalidatepage(struct page *page, unsigned int offset,
			       unsigned int length)
{
	struct afs_vnode *vnode = AFS_FS_I(page->mapping->host);
	unsigned long priv;

	_enter("{%lu},%u,%u", page->index, offset, length);

	BUG_ON(!PageLocked(page));

	/* we clean up only if the entire page is being invalidated */
	if (offset == 0 && length == PAGE_SIZE) {
#ifdef CONFIG_AFS_FSCACHE
		if (PageFsCache(page)) {
			struct afs_vnode *vnode = AFS_FS_I(page->mapping->host);
			fscache_wait_on_page_write(vnode->cache, page);
			fscache_uncache_page(vnode->cache, page);
		}
#endif

		if (PagePrivate(page)) {
			priv = page_private(page);
			trace_afs_page_dirty(vnode, tracepoint_string("inval"),
					     page->index, priv);
			set_page_private(page, 0);
			ClearPagePrivate(page);
		}
	}

	_leave("");
}