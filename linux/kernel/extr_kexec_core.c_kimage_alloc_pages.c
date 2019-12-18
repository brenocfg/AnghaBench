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
struct page {int /*<<< orphan*/ * mapping; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  SetPageReserved (struct page*) ; 
 int __GFP_ZERO ; 
 struct page* alloc_pages (int,unsigned int) ; 
 int /*<<< orphan*/  arch_kexec_post_alloc_pages (int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  clear_highpage (struct page*) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ fatal_signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 int /*<<< orphan*/  set_page_private (struct page*,unsigned int) ; 

__attribute__((used)) static struct page *kimage_alloc_pages(gfp_t gfp_mask, unsigned int order)
{
	struct page *pages;

	if (fatal_signal_pending(current))
		return NULL;
	pages = alloc_pages(gfp_mask & ~__GFP_ZERO, order);
	if (pages) {
		unsigned int count, i;

		pages->mapping = NULL;
		set_page_private(pages, order);
		count = 1 << order;
		for (i = 0; i < count; i++)
			SetPageReserved(pages + i);

		arch_kexec_post_alloc_pages(page_address(pages), count,
					    gfp_mask);

		if (gfp_mask & __GFP_ZERO)
			for (i = 0; i < count; i++)
				clear_highpage(pages + i);
	}

	return pages;
}