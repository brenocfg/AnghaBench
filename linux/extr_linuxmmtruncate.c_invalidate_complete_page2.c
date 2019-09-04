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
struct page {struct address_space* mapping; } ;
struct address_space {int /*<<< orphan*/  i_pages; TYPE_1__* a_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* freepage ) (struct page*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (scalar_t__) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ PageDirty (struct page*) ; 
 int /*<<< orphan*/  __delete_from_page_cache (struct page*,int /*<<< orphan*/ *) ; 
 scalar_t__ page_has_private (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  stub1 (struct page*) ; 
 int /*<<< orphan*/  try_to_release_page (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  xa_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
invalidate_complete_page2(struct address_space *mapping, struct page *page)
{
	unsigned long flags;

	if (page->mapping != mapping)
		return 0;

	if (page_has_private(page) && !try_to_release_page(page, GFP_KERNEL))
		return 0;

	xa_lock_irqsave(&mapping->i_pages, flags);
	if (PageDirty(page))
		goto failed;

	BUG_ON(page_has_private(page));
	__delete_from_page_cache(page, NULL);
	xa_unlock_irqrestore(&mapping->i_pages, flags);

	if (mapping->a_ops->freepage)
		mapping->a_ops->freepage(page);

	put_page(page);	/* pagecache ref */
	return 1;
failed:
	xa_unlock_irqrestore(&mapping->i_pages, flags);
	return 0;
}