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

/* Variables and functions */
 int MF_DELAYED ; 
 int MF_RECOVERED ; 
 scalar_t__ PageAnon (struct page*) ; 
 int /*<<< orphan*/  PageHuge (struct page*) ; 
 struct page* compound_head (struct page*) ; 
 int /*<<< orphan*/  dissolve_free_huge_page (struct page*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 struct address_space* page_mapping (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int truncate_error_page (struct page*,unsigned long,struct address_space*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int me_huge_page(struct page *p, unsigned long pfn)
{
	int res = 0;
	struct page *hpage = compound_head(p);
	struct address_space *mapping;

	if (!PageHuge(hpage))
		return MF_DELAYED;

	mapping = page_mapping(hpage);
	if (mapping) {
		res = truncate_error_page(hpage, pfn, mapping);
	} else {
		unlock_page(hpage);
		/*
		 * migration entry prevents later access on error anonymous
		 * hugepage, so we can free and dissolve it into buddy to
		 * save healthy subpages.
		 */
		if (PageAnon(hpage))
			put_page(hpage);
		dissolve_free_huge_page(p);
		res = MF_RECOVERED;
		lock_page(hpage);
	}

	return res;
}