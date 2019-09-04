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
struct page {int /*<<< orphan*/  index; struct address_space* mapping; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct address_space {int /*<<< orphan*/  i_pages; struct inode* host; } ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 struct address_space* READ_ONCE (struct address_space*) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 void* __radix_tree_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void***) ; 
 int /*<<< orphan*/  dax_mapping (struct address_space*) ; 
 int /*<<< orphan*/  lock_slot (struct address_space*,void**) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ slot_locked (struct address_space*,void**) ; 
 int /*<<< orphan*/  wait_entry_unlocked (struct address_space*,int /*<<< orphan*/ ,void***,void*) ; 
 int /*<<< orphan*/  xa_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_unlock_irq (int /*<<< orphan*/ *) ; 

bool dax_lock_mapping_entry(struct page *page)
{
	pgoff_t index;
	struct inode *inode;
	bool did_lock = false;
	void *entry = NULL, **slot;
	struct address_space *mapping;

	rcu_read_lock();
	for (;;) {
		mapping = READ_ONCE(page->mapping);

		if (!mapping || !dax_mapping(mapping))
			break;

		/*
		 * In the device-dax case there's no need to lock, a
		 * struct dev_pagemap pin is sufficient to keep the
		 * inode alive, and we assume we have dev_pagemap pin
		 * otherwise we would not have a valid pfn_to_page()
		 * translation.
		 */
		inode = mapping->host;
		if (S_ISCHR(inode->i_mode)) {
			did_lock = true;
			break;
		}

		xa_lock_irq(&mapping->i_pages);
		if (mapping != page->mapping) {
			xa_unlock_irq(&mapping->i_pages);
			continue;
		}
		index = page->index;

		entry = __radix_tree_lookup(&mapping->i_pages, index,
						NULL, &slot);
		if (!entry) {
			xa_unlock_irq(&mapping->i_pages);
			break;
		} else if (slot_locked(mapping, slot)) {
			rcu_read_unlock();
			wait_entry_unlocked(mapping, index, &slot, entry);
			rcu_read_lock();
			continue;
		}
		lock_slot(mapping, slot);
		did_lock = true;
		xa_unlock_irq(&mapping->i_pages);
		break;
	}
	rcu_read_unlock();

	return did_lock;
}