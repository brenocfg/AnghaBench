#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct page {int /*<<< orphan*/  index; struct address_space* mapping; } ;
struct address_space {int /*<<< orphan*/  i_pages; TYPE_1__* host; } ;
typedef  int /*<<< orphan*/  dax_entry_t ;
struct TYPE_11__ {int /*<<< orphan*/ * xa; } ;
struct TYPE_10__ {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 struct address_space* READ_ONCE (struct address_space*) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XA_STATE (TYPE_2__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dax_is_locked (void*) ; 
 int /*<<< orphan*/  dax_lock_entry (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  dax_mapping (struct address_space*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  wait_entry_unlocked (TYPE_2__*,void*) ; 
 TYPE_2__ xas ; 
 void* xas_load (TYPE_2__*) ; 
 int /*<<< orphan*/  xas_lock_irq (TYPE_2__*) ; 
 int /*<<< orphan*/  xas_set (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xas_unlock_irq (TYPE_2__*) ; 

dax_entry_t dax_lock_page(struct page *page)
{
	XA_STATE(xas, NULL, 0);
	void *entry;

	/* Ensure page->mapping isn't freed while we look at it */
	rcu_read_lock();
	for (;;) {
		struct address_space *mapping = READ_ONCE(page->mapping);

		entry = NULL;
		if (!mapping || !dax_mapping(mapping))
			break;

		/*
		 * In the device-dax case there's no need to lock, a
		 * struct dev_pagemap pin is sufficient to keep the
		 * inode alive, and we assume we have dev_pagemap pin
		 * otherwise we would not have a valid pfn_to_page()
		 * translation.
		 */
		entry = (void *)~0UL;
		if (S_ISCHR(mapping->host->i_mode))
			break;

		xas.xa = &mapping->i_pages;
		xas_lock_irq(&xas);
		if (mapping != page->mapping) {
			xas_unlock_irq(&xas);
			continue;
		}
		xas_set(&xas, page->index);
		entry = xas_load(&xas);
		if (dax_is_locked(entry)) {
			rcu_read_unlock();
			wait_entry_unlocked(&xas, entry);
			rcu_read_lock();
			continue;
		}
		dax_lock_entry(&xas, entry);
		xas_unlock_irq(&xas);
		break;
	}
	rcu_read_unlock();
	return (dax_entry_t)entry;
}