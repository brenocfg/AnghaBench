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
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  pgoff_t ;
typedef  int gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  PageActive (struct page*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ClearPageLocked (struct page*) ; 
 int __GFP_WRITE ; 
 int /*<<< orphan*/  __SetPageLocked (struct page*) ; 
 int __add_to_page_cache_locked (struct page*,struct address_space*,int /*<<< orphan*/ ,int,void**) ; 
 int /*<<< orphan*/  lru_cache_add (struct page*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  workingset_refault (struct page*,void*) ; 

int add_to_page_cache_lru(struct page *page, struct address_space *mapping,
				pgoff_t offset, gfp_t gfp_mask)
{
	void *shadow = NULL;
	int ret;

	__SetPageLocked(page);
	ret = __add_to_page_cache_locked(page, mapping, offset,
					 gfp_mask, &shadow);
	if (unlikely(ret))
		__ClearPageLocked(page);
	else {
		/*
		 * The page might have been evicted from cache only
		 * recently, in which case it should be activated like
		 * any other repeatedly accessed page.
		 * The exception is pages getting rewritten; evicting other
		 * data from the working set, only to cache data that will
		 * get overwritten with something else, is a waste of memory.
		 */
		WARN_ON_ONCE(PageActive(page));
		if (!(gfp_mask & __GFP_WRITE) && shadow)
			workingset_refault(page, shadow);
		lru_cache_add(page);
	}
	return ret;
}