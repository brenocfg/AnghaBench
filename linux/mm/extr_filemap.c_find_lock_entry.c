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
typedef  scalar_t__ pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 struct page* find_get_entry (struct address_space*,scalar_t__) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 struct address_space* page_mapping (struct page*) ; 
 scalar_t__ page_to_pgoff (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  xa_is_value (struct page*) ; 

struct page *find_lock_entry(struct address_space *mapping, pgoff_t offset)
{
	struct page *page;

repeat:
	page = find_get_entry(mapping, offset);
	if (page && !xa_is_value(page)) {
		lock_page(page);
		/* Has the page been truncated? */
		if (unlikely(page_mapping(page) != mapping)) {
			unlock_page(page);
			put_page(page);
			goto repeat;
		}
		VM_BUG_ON_PAGE(page_to_pgoff(page) != offset, page);
	}
	return page;
}