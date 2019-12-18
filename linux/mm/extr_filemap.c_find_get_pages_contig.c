#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct address_space {int /*<<< orphan*/  i_pages; } ;
typedef  int /*<<< orphan*/  pgoff_t ;
struct TYPE_8__ {int /*<<< orphan*/  xa_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  XA_STATE (TYPE_1__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct page* find_subpage (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_cache_get_speculative (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ xa_is_value (struct page*) ; 
 TYPE_1__ xas ; 
 struct page* xas_load (TYPE_1__*) ; 
 struct page* xas_next (TYPE_1__*) ; 
 struct page* xas_reload (TYPE_1__*) ; 
 int /*<<< orphan*/  xas_reset (TYPE_1__*) ; 
 scalar_t__ xas_retry (TYPE_1__*,struct page*) ; 

unsigned find_get_pages_contig(struct address_space *mapping, pgoff_t index,
			       unsigned int nr_pages, struct page **pages)
{
	XA_STATE(xas, &mapping->i_pages, index);
	struct page *page;
	unsigned int ret = 0;

	if (unlikely(!nr_pages))
		return 0;

	rcu_read_lock();
	for (page = xas_load(&xas); page; page = xas_next(&xas)) {
		if (xas_retry(&xas, page))
			continue;
		/*
		 * If the entry has been swapped out, we can stop looking.
		 * No current caller is looking for DAX entries.
		 */
		if (xa_is_value(page))
			break;

		if (!page_cache_get_speculative(page))
			goto retry;

		/* Has the page moved or been split? */
		if (unlikely(page != xas_reload(&xas)))
			goto put_page;

		pages[ret] = find_subpage(page, xas.xa_index);
		if (++ret == nr_pages)
			break;
		continue;
put_page:
		put_page(page);
retry:
		xas_reset(&xas);
	}
	rcu_read_unlock();
	return ret;
}