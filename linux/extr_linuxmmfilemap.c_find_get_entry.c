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
typedef  void page ;
struct address_space {int /*<<< orphan*/  i_pages; } ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 void* compound_head (void*) ; 
 int /*<<< orphan*/  page_cache_get_speculative (void*) ; 
 int /*<<< orphan*/  put_page (void*) ; 
 scalar_t__ radix_tree_deref_retry (void*) ; 
 void* radix_tree_deref_slot (void**) ; 
 scalar_t__ radix_tree_exception (void*) ; 
 void** radix_tree_lookup_slot (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ unlikely (int) ; 

struct page *find_get_entry(struct address_space *mapping, pgoff_t offset)
{
	void **pagep;
	struct page *head, *page;

	rcu_read_lock();
repeat:
	page = NULL;
	pagep = radix_tree_lookup_slot(&mapping->i_pages, offset);
	if (pagep) {
		page = radix_tree_deref_slot(pagep);
		if (unlikely(!page))
			goto out;
		if (radix_tree_exception(page)) {
			if (radix_tree_deref_retry(page))
				goto repeat;
			/*
			 * A shadow entry of a recently evicted page,
			 * or a swap entry from shmem/tmpfs.  Return
			 * it without attempting to raise page count.
			 */
			goto out;
		}

		head = compound_head(page);
		if (!page_cache_get_speculative(head))
			goto repeat;

		/* The page was split under us? */
		if (compound_head(page) != head) {
			put_page(head);
			goto repeat;
		}

		/*
		 * Has the page moved?
		 * This is part of the lockless pagecache protocol. See
		 * include/linux/pagemap.h for details.
		 */
		if (unlikely(page != *pagep)) {
			put_page(head);
			goto repeat;
		}
	}
out:
	rcu_read_unlock();

	return page;
}