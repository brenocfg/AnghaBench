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
struct pagevec {int /*<<< orphan*/ * pages; } ;
struct address_space {int /*<<< orphan*/  i_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  page_cache_delete_batch (struct address_space*,struct pagevec*) ; 
 int /*<<< orphan*/  page_cache_free_page (struct address_space*,int /*<<< orphan*/ ) ; 
 int pagevec_count (struct pagevec*) ; 
 int /*<<< orphan*/  trace_mm_filemap_delete_from_page_cache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unaccount_page_cache_page (struct address_space*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  xa_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void delete_from_page_cache_batch(struct address_space *mapping,
				  struct pagevec *pvec)
{
	int i;
	unsigned long flags;

	if (!pagevec_count(pvec))
		return;

	xa_lock_irqsave(&mapping->i_pages, flags);
	for (i = 0; i < pagevec_count(pvec); i++) {
		trace_mm_filemap_delete_from_page_cache(pvec->pages[i]);

		unaccount_page_cache_page(mapping, pvec->pages[i]);
	}
	page_cache_delete_batch(mapping, pvec);
	xa_unlock_irqrestore(&mapping->i_pages, flags);

	for (i = 0; i < pagevec_count(pvec); i++)
		page_cache_free_page(mapping, pvec->pages[i]);
}