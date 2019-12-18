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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  swp_entry_t ;
struct mm_walk {int /*<<< orphan*/  mm; struct hmm_vma_walk* private; } ;
struct hmm_vma_walk {unsigned long last; int /*<<< orphan*/ * pgmap; struct hmm_range* range; } ;
struct hmm_range {int* values; int* flags; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ARCH_HAS_PTE_SPECIAL ; 
 int EBUSY ; 
 int EFAULT ; 
 size_t HMM_PFN_DEVICE_PRIVATE ; 
 size_t HMM_PFN_ERROR ; 
 size_t HMM_PFN_NONE ; 
 size_t HMM_PFN_SPECIAL ; 
 size_t HMM_PFN_VALID ; 
 size_t HMM_PFN_WRITE ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_dev_pagemap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hmm_device_entry_from_pfn (struct hmm_range*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hmm_pte_need_fault (struct hmm_vma_walk*,int,int,int*,int*) ; 
 int hmm_vma_walk_hole_ (unsigned long,unsigned long,int,int,struct mm_walk*) ; 
 scalar_t__ is_device_private_entry (int /*<<< orphan*/ ) ; 
 scalar_t__ is_migration_entry (int /*<<< orphan*/ ) ; 
 scalar_t__ is_write_device_private_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  migration_entry_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  non_swap_entry (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_devmap (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_present (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_special (int /*<<< orphan*/ ) ; 
 int pte_to_hmm_pfn_flags (struct hmm_range*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_to_swp_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_unmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_dev_pagemap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swp_offset (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int hmm_vma_handle_pte(struct mm_walk *walk, unsigned long addr,
			      unsigned long end, pmd_t *pmdp, pte_t *ptep,
			      uint64_t *pfn)
{
	struct hmm_vma_walk *hmm_vma_walk = walk->private;
	struct hmm_range *range = hmm_vma_walk->range;
	bool fault, write_fault;
	uint64_t cpu_flags;
	pte_t pte = *ptep;
	uint64_t orig_pfn = *pfn;

	*pfn = range->values[HMM_PFN_NONE];
	fault = write_fault = false;

	if (pte_none(pte)) {
		hmm_pte_need_fault(hmm_vma_walk, orig_pfn, 0,
				   &fault, &write_fault);
		if (fault || write_fault)
			goto fault;
		return 0;
	}

	if (!pte_present(pte)) {
		swp_entry_t entry = pte_to_swp_entry(pte);

		if (!non_swap_entry(entry)) {
			cpu_flags = pte_to_hmm_pfn_flags(range, pte);
			hmm_pte_need_fault(hmm_vma_walk, orig_pfn, cpu_flags,
					   &fault, &write_fault);
			if (fault || write_fault)
				goto fault;
			return 0;
		}

		/*
		 * This is a special swap entry, ignore migration, use
		 * device and report anything else as error.
		 */
		if (is_device_private_entry(entry)) {
			cpu_flags = range->flags[HMM_PFN_VALID] |
				range->flags[HMM_PFN_DEVICE_PRIVATE];
			cpu_flags |= is_write_device_private_entry(entry) ?
				range->flags[HMM_PFN_WRITE] : 0;
			hmm_pte_need_fault(hmm_vma_walk, orig_pfn, cpu_flags,
					   &fault, &write_fault);
			if (fault || write_fault)
				goto fault;
			*pfn = hmm_device_entry_from_pfn(range,
					    swp_offset(entry));
			*pfn |= cpu_flags;
			return 0;
		}

		if (is_migration_entry(entry)) {
			if (fault || write_fault) {
				pte_unmap(ptep);
				hmm_vma_walk->last = addr;
				migration_entry_wait(walk->mm, pmdp, addr);
				return -EBUSY;
			}
			return 0;
		}

		/* Report error for everything else */
		*pfn = range->values[HMM_PFN_ERROR];
		return -EFAULT;
	} else {
		cpu_flags = pte_to_hmm_pfn_flags(range, pte);
		hmm_pte_need_fault(hmm_vma_walk, orig_pfn, cpu_flags,
				   &fault, &write_fault);
	}

	if (fault || write_fault)
		goto fault;

	if (pte_devmap(pte)) {
		hmm_vma_walk->pgmap = get_dev_pagemap(pte_pfn(pte),
					      hmm_vma_walk->pgmap);
		if (unlikely(!hmm_vma_walk->pgmap))
			return -EBUSY;
	} else if (IS_ENABLED(CONFIG_ARCH_HAS_PTE_SPECIAL) && pte_special(pte)) {
		*pfn = range->values[HMM_PFN_SPECIAL];
		return -EFAULT;
	}

	*pfn = hmm_device_entry_from_pfn(range, pte_pfn(pte)) | cpu_flags;
	return 0;

fault:
	if (hmm_vma_walk->pgmap) {
		put_dev_pagemap(hmm_vma_walk->pgmap);
		hmm_vma_walk->pgmap = NULL;
	}
	pte_unmap(ptep);
	/* Fault any virtual address we were asked to fault */
	return hmm_vma_walk_hole_(addr, end, fault, write_fault, walk);
}