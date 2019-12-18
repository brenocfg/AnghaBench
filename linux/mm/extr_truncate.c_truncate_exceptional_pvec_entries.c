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
struct pagevec {int nr; struct page** pages; } ;
struct page {int dummy; } ;
struct address_space {int /*<<< orphan*/  i_pages; } ;
typedef  scalar_t__ pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_shadow_entry (struct address_space*,scalar_t__,struct page*) ; 
 int /*<<< orphan*/  dax_delete_mapping_entry (struct address_space*,scalar_t__) ; 
 int dax_mapping (struct address_space*) ; 
 int pagevec_count (struct pagevec*) ; 
 scalar_t__ shmem_mapping (struct address_space*) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ xa_is_value (struct page*) ; 
 int /*<<< orphan*/  xa_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void truncate_exceptional_pvec_entries(struct address_space *mapping,
				struct pagevec *pvec, pgoff_t *indices,
				pgoff_t end)
{
	int i, j;
	bool dax, lock;

	/* Handled by shmem itself */
	if (shmem_mapping(mapping))
		return;

	for (j = 0; j < pagevec_count(pvec); j++)
		if (xa_is_value(pvec->pages[j]))
			break;

	if (j == pagevec_count(pvec))
		return;

	dax = dax_mapping(mapping);
	lock = !dax && indices[j] < end;
	if (lock)
		xa_lock_irq(&mapping->i_pages);

	for (i = j; i < pagevec_count(pvec); i++) {
		struct page *page = pvec->pages[i];
		pgoff_t index = indices[i];

		if (!xa_is_value(page)) {
			pvec->pages[j++] = page;
			continue;
		}

		if (index >= end)
			continue;

		if (unlikely(dax)) {
			dax_delete_mapping_entry(mapping, index);
			continue;
		}

		__clear_shadow_entry(mapping, index, page);
	}

	if (lock)
		xa_unlock_irq(&mapping->i_pages);
	pvec->nr = j;
}