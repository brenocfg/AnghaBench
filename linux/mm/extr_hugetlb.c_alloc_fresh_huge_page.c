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
 struct page* alloc_buddy_huge_page (struct hstate*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct page* alloc_gigantic_page (struct hstate*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ hstate_is_gigantic (struct hstate*) ; 
 int /*<<< orphan*/  huge_page_order (struct hstate*) ; 
 int /*<<< orphan*/  page_to_nid (struct page*) ; 
 int /*<<< orphan*/  prep_compound_gigantic_page (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prep_new_huge_page (struct hstate*,struct page*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct page *alloc_fresh_huge_page(struct hstate *h,
		gfp_t gfp_mask, int nid, nodemask_t *nmask,
		nodemask_t *node_alloc_noretry)
{
	struct page *page;

	if (hstate_is_gigantic(h))
		page = alloc_gigantic_page(h, gfp_mask, nid, nmask);
	else
		page = alloc_buddy_huge_page(h, gfp_mask,
				nid, nmask, node_alloc_noretry);
	if (!page)
		return NULL;

	if (hstate_is_gigantic(h))
		prep_compound_gigantic_page(page, huge_page_order(h));
	prep_new_huge_page(h, page, page_to_nid(page));

	return page;
}