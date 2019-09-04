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
struct afs_read {size_t index; struct page** pages; } ;
struct afs_call {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static void afs_readpages_page_done(struct afs_call *call, struct afs_read *req)
{
#ifdef CONFIG_AFS_FSCACHE
	struct afs_vnode *vnode = call->reply[0];
#endif
	struct page *page = req->pages[req->index];

	req->pages[req->index] = NULL;
	SetPageUptodate(page);

	/* send the page to the cache */
#ifdef CONFIG_AFS_FSCACHE
	if (PageFsCache(page) &&
	    fscache_write_page(vnode->cache, page, vnode->status.size,
			       GFP_KERNEL) != 0) {
		fscache_uncache_page(vnode->cache, page);
		BUG_ON(PageFsCache(page));
	}
#endif
	unlock_page(page);
	put_page(page);
}