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
struct hstate {int dummy; } ;
typedef  int /*<<< orphan*/  nodemask_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  SetPageHugeTemporary (struct page*) ; 
 struct page* alloc_fresh_huge_page (struct hstate*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ hstate_is_gigantic (struct hstate*) ; 

struct page *alloc_migrate_huge_page(struct hstate *h, gfp_t gfp_mask,
				     int nid, nodemask_t *nmask)
{
	struct page *page;

	if (hstate_is_gigantic(h))
		return NULL;

	page = alloc_fresh_huge_page(h, gfp_mask, nid, nmask, NULL);
	if (!page)
		return NULL;

	/*
	 * We do not account these pages as surplus because they are only
	 * temporary and will be released properly on the last reference
	 */
	SetPageHugeTemporary(page);

	return page;
}