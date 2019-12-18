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
typedef  int /*<<< orphan*/  uint64_t ;
struct hmm_vma_walk {int flags; } ;

/* Variables and functions */
 int HMM_FAULT_SNAPSHOT ; 
 int /*<<< orphan*/  hmm_pte_need_fault (struct hmm_vma_walk const*,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static void hmm_range_need_fault(const struct hmm_vma_walk *hmm_vma_walk,
				 const uint64_t *pfns, unsigned long npages,
				 uint64_t cpu_flags, bool *fault,
				 bool *write_fault)
{
	unsigned long i;

	if (hmm_vma_walk->flags & HMM_FAULT_SNAPSHOT) {
		*fault = *write_fault = false;
		return;
	}

	*fault = *write_fault = false;
	for (i = 0; i < npages; ++i) {
		hmm_pte_need_fault(hmm_vma_walk, pfns[i], cpu_flags,
				   fault, write_fault);
		if ((*write_fault))
			return;
	}
}