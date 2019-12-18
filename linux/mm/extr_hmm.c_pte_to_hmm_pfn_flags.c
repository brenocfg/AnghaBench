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
struct hmm_range {int* flags; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 size_t HMM_PFN_VALID ; 
 size_t HMM_PFN_WRITE ; 
 scalar_t__ pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_present (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_protnone (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_write (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint64_t pte_to_hmm_pfn_flags(struct hmm_range *range, pte_t pte)
{
	if (pte_none(pte) || !pte_present(pte) || pte_protnone(pte))
		return 0;
	return pte_write(pte) ? range->flags[HMM_PFN_VALID] |
				range->flags[HMM_PFN_WRITE] :
				range->flags[HMM_PFN_VALID];
}