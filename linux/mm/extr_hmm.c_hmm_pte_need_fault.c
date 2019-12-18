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
struct hmm_vma_walk {int flags; struct hmm_range* range; } ;
struct hmm_range {int pfn_flags_mask; int default_flags; int* flags; } ;

/* Variables and functions */
 int HMM_FAULT_SNAPSHOT ; 
 size_t HMM_PFN_DEVICE_PRIVATE ; 
 size_t HMM_PFN_VALID ; 
 size_t HMM_PFN_WRITE ; 

__attribute__((used)) static inline void hmm_pte_need_fault(const struct hmm_vma_walk *hmm_vma_walk,
				      uint64_t pfns, uint64_t cpu_flags,
				      bool *fault, bool *write_fault)
{
	struct hmm_range *range = hmm_vma_walk->range;

	if (hmm_vma_walk->flags & HMM_FAULT_SNAPSHOT)
		return;

	/*
	 * So we not only consider the individual per page request we also
	 * consider the default flags requested for the range. The API can
	 * be used 2 ways. The first one where the HMM user coalesces
	 * multiple page faults into one request and sets flags per pfn for
	 * those faults. The second one where the HMM user wants to pre-
	 * fault a range with specific flags. For the latter one it is a
	 * waste to have the user pre-fill the pfn arrays with a default
	 * flags value.
	 */
	pfns = (pfns & range->pfn_flags_mask) | range->default_flags;

	/* We aren't ask to do anything ... */
	if (!(pfns & range->flags[HMM_PFN_VALID]))
		return;
	/* If this is device memory then only fault if explicitly requested */
	if ((cpu_flags & range->flags[HMM_PFN_DEVICE_PRIVATE])) {
		/* Do we fault on device memory ? */
		if (pfns & range->flags[HMM_PFN_DEVICE_PRIVATE]) {
			*write_fault = pfns & range->flags[HMM_PFN_WRITE];
			*fault = true;
		}
		return;
	}

	/* If CPU page table is not valid then we need to fault */
	*fault = !(cpu_flags & range->flags[HMM_PFN_VALID]);
	/* Need to write fault ? */
	if ((pfns & range->flags[HMM_PFN_WRITE]) &&
	    !(cpu_flags & range->flags[HMM_PFN_WRITE])) {
		*write_fault = true;
		*fault = true;
	}
}