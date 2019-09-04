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
typedef  int gfp_t ;

/* Variables and functions */
 int __GFP_NOFAIL ; 
 struct page* alloc_pages (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 struct page* lru_to_page (struct list_head*) ; 

struct page *erofs_allocpage(struct list_head *pool, gfp_t gfp)
{
	struct page *page;

	if (!list_empty(pool)) {
		page = lru_to_page(pool);
		list_del(&page->lru);
	} else {
		page = alloc_pages(gfp | __GFP_NOFAIL, 0);
	}
	return page;
}