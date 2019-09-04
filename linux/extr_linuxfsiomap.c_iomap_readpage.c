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
struct page {TYPE_1__* mapping; } ;
struct iomap_readpage_ctx {int cur_page_in_bio; scalar_t__ bio; struct page* cur_page; } ;
struct iomap_ops {int dummy; } ;
struct inode {int dummy; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  SetPageError (struct page*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ iomap_apply (struct inode*,scalar_t__,unsigned int,int /*<<< orphan*/ ,struct iomap_ops const*,struct iomap_readpage_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iomap_readpage_actor ; 
 scalar_t__ page_offset (struct page*) ; 
 int /*<<< orphan*/  submit_bio (scalar_t__) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int
iomap_readpage(struct page *page, const struct iomap_ops *ops)
{
	struct iomap_readpage_ctx ctx = { .cur_page = page };
	struct inode *inode = page->mapping->host;
	unsigned poff;
	loff_t ret;

	for (poff = 0; poff < PAGE_SIZE; poff += ret) {
		ret = iomap_apply(inode, page_offset(page) + poff,
				PAGE_SIZE - poff, 0, ops, &ctx,
				iomap_readpage_actor);
		if (ret <= 0) {
			WARN_ON_ONCE(ret == 0);
			SetPageError(page);
			break;
		}
	}

	if (ctx.bio) {
		submit_bio(ctx.bio);
		WARN_ON_ONCE(!ctx.cur_page_in_bio);
	} else {
		WARN_ON_ONCE(ctx.cur_page_in_bio);
		unlock_page(page);
	}

	/*
	 * Just like mpage_readpages and block_read_full_page we always
	 * return 0 and just mark the page as PageError on errors.  This
	 * should be cleaned up all through the stack eventually.
	 */
	return 0;
}