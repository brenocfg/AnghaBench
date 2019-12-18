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
struct buffer_head {struct buffer_head* b_this_page; } ;
struct TYPE_2__ {int /*<<< orphan*/  private_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ PageDirty (struct page*) ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int /*<<< orphan*/  attach_page_buffers (struct page*,struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void attach_nobh_buffers(struct page *page, struct buffer_head *head)
{
	struct buffer_head *bh;

	BUG_ON(!PageLocked(page));

	spin_lock(&page->mapping->private_lock);
	bh = head;
	do {
		if (PageDirty(page))
			set_buffer_dirty(bh);
		if (!bh->b_this_page)
			bh->b_this_page = head;
		bh = bh->b_this_page;
	} while (bh != head);
	attach_page_buffers(page, head);
	spin_unlock(&page->mapping->private_lock);
}