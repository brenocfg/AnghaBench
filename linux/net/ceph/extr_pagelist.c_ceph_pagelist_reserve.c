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
struct ceph_pagelist {size_t room; size_t num_pages_free; int /*<<< orphan*/  free_list; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 size_t PAGE_SHIFT ; 
 size_t PAGE_SIZE ; 
 struct page* __page_cache_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int ceph_pagelist_reserve(struct ceph_pagelist *pl, size_t space)
{
	if (space <= pl->room)
		return 0;
	space -= pl->room;
	space = (space + PAGE_SIZE - 1) >> PAGE_SHIFT;   /* conv to num pages */

	while (space > pl->num_pages_free) {
		struct page *page = __page_cache_alloc(GFP_NOFS);
		if (!page)
			return -ENOMEM;
		list_add_tail(&page->lru, &pl->free_list);
		++pl->num_pages_free;
	}
	return 0;
}