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
struct address_space {int /*<<< orphan*/  i_pages; } ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  XA_STATE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct page* find_subpage (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_cache_get_speculative (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ xa_is_value (struct page*) ; 
 int /*<<< orphan*/  xas ; 
 struct page* xas_load (int /*<<< orphan*/ *) ; 
 struct page* xas_reload (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xas_reset (int /*<<< orphan*/ *) ; 
 scalar_t__ xas_retry (int /*<<< orphan*/ *,struct page*) ; 

struct page *find_get_entry(struct address_space *mapping, pgoff_t offset)
{
	XA_STATE(xas, &mapping->i_pages, offset);
	struct page *page;

	rcu_read_lock();
repeat:
	xas_reset(&xas);
	page = xas_load(&xas);
	if (xas_retry(&xas, page))
		goto repeat;
	/*
	 * A shadow entry of a recently evicted page, or a swap entry from
	 * shmem/tmpfs.  Return it without attempting to raise page count.
	 */
	if (!page || xa_is_value(page))
		goto out;

	if (!page_cache_get_speculative(page))
		goto repeat;

	/*
	 * Has the page moved or been split?
	 * This is part of the lockless pagecache protocol. See
	 * include/linux/pagemap.h for details.
	 */
	if (unlikely(page != xas_reload(&xas))) {
		put_page(page);
		goto repeat;
	}
	page = find_subpage(page, offset);
out:
	rcu_read_unlock();

	return page;
}