#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  swp_entry_t ;
struct page_vma_mapped_walk {int flags; int /*<<< orphan*/  ptl; int /*<<< orphan*/  pmd; TYPE_1__* vma; int /*<<< orphan*/ * pte; int /*<<< orphan*/  address; } ;
struct TYPE_2__ {int /*<<< orphan*/  vm_mm; } ;

/* Variables and functions */
 int PVMW_MIGRATION ; 
 int PVMW_SYNC ; 
 int /*<<< orphan*/  is_device_private_entry (int /*<<< orphan*/ ) ; 
 scalar_t__ is_swap_pte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_lockptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_to_swp_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool map_pte(struct page_vma_mapped_walk *pvmw)
{
	pvmw->pte = pte_offset_map(pvmw->pmd, pvmw->address);
	if (!(pvmw->flags & PVMW_SYNC)) {
		if (pvmw->flags & PVMW_MIGRATION) {
			if (!is_swap_pte(*pvmw->pte))
				return false;
		} else {
			/*
			 * We get here when we are trying to unmap a private
			 * device page from the process address space. Such
			 * page is not CPU accessible and thus is mapped as
			 * a special swap entry, nonetheless it still does
			 * count as a valid regular mapping for the page (and
			 * is accounted as such in page maps count).
			 *
			 * So handle this special case as if it was a normal
			 * page mapping ie lock CPU page table and returns
			 * true.
			 *
			 * For more details on device private memory see HMM
			 * (include/linux/hmm.h or mm/hmm.c).
			 */
			if (is_swap_pte(*pvmw->pte)) {
				swp_entry_t entry;

				/* Handle un-addressable ZONE_DEVICE memory */
				entry = pte_to_swp_entry(*pvmw->pte);
				if (!is_device_private_entry(entry))
					return false;
			} else if (!pte_present(*pvmw->pte))
				return false;
		}
	}
	pvmw->ptl = pte_lockptr(pvmw->vma->vm_mm, pvmw->pmd);
	spin_lock(pvmw->ptl);
	return true;
}