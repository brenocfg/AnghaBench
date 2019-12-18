#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ swp_entry_t ;
struct page {int dummy; } ;
struct address_space {int /*<<< orphan*/  i_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  __delete_from_swap_cache (struct page*,TYPE_1__) ; 
 int /*<<< orphan*/  hpage_nr_pages (struct page*) ; 
 int /*<<< orphan*/  page_private (struct page*) ; 
 int /*<<< orphan*/  page_ref_sub (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_swap_page (struct page*,TYPE_1__) ; 
 struct address_space* swap_address_space (TYPE_1__) ; 
 int /*<<< orphan*/  xa_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_unlock_irq (int /*<<< orphan*/ *) ; 

void delete_from_swap_cache(struct page *page)
{
	swp_entry_t entry = { .val = page_private(page) };
	struct address_space *address_space = swap_address_space(entry);

	xa_lock_irq(&address_space->i_pages);
	__delete_from_swap_cache(page, entry);
	xa_unlock_irq(&address_space->i_pages);

	put_swap_page(page, entry);
	page_ref_sub(page, hpage_nr_pages(page));
}