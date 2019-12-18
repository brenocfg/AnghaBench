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
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 size_t HMM_PFN_VALID ; 
 size_t HMM_PFN_WRITE ; 
 scalar_t__ pmd_protnone (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_write (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint64_t pmd_to_hmm_pfn_flags(struct hmm_range *range, pmd_t pmd)
{
	if (pmd_protnone(pmd))
		return 0;
	return pmd_write(pmd) ? range->flags[HMM_PFN_VALID] |
				range->flags[HMM_PFN_WRITE] :
				range->flags[HMM_PFN_VALID];
}