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
typedef  int /*<<< orphan*/  swp_entry_t ;
struct page_vma_mapped_walk {int flags; int /*<<< orphan*/  page; int /*<<< orphan*/ * pte; } ;

/* Variables and functions */
 int PVMW_MIGRATION ; 
 unsigned long device_private_entry_to_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_device_private_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_migration_entry (int /*<<< orphan*/ ) ; 
 scalar_t__ is_swap_pte (int /*<<< orphan*/ ) ; 
 unsigned long migration_entry_to_pfn (int /*<<< orphan*/ ) ; 
 int pfn_in_hpage (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long pte_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_to_swp_entry (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool check_pte(struct page_vma_mapped_walk *pvmw)
{
	unsigned long pfn;

	if (pvmw->flags & PVMW_MIGRATION) {
		swp_entry_t entry;
		if (!is_swap_pte(*pvmw->pte))
			return false;
		entry = pte_to_swp_entry(*pvmw->pte);

		if (!is_migration_entry(entry))
			return false;

		pfn = migration_entry_to_pfn(entry);
	} else if (is_swap_pte(*pvmw->pte)) {
		swp_entry_t entry;

		/* Handle un-addressable ZONE_DEVICE memory */
		entry = pte_to_swp_entry(*pvmw->pte);
		if (!is_device_private_entry(entry))
			return false;

		pfn = device_private_entry_to_pfn(entry);
	} else {
		if (!pte_present(*pvmw->pte))
			return false;

		pfn = pte_pfn(*pvmw->pte);
	}

	return pfn_in_hpage(pvmw->page, pfn);
}