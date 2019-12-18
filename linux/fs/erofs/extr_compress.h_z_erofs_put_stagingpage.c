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
struct page {int /*<<< orphan*/  lru; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 int page_ref_count (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  z_erofs_page_is_staging (struct page*) ; 

__attribute__((used)) static inline bool z_erofs_put_stagingpage(struct list_head *pagepool,
					   struct page *page)
{
	if (!z_erofs_page_is_staging(page))
		return false;

	/* staging pages should not be used by others at the same time */
	if (page_ref_count(page) > 1)
		put_page(page);
	else
		list_add(&page->lru, pagepool);
	return true;
}