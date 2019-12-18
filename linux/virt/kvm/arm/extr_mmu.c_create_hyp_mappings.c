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
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 unsigned long PAGE_ALIGN (unsigned long) ; 
 unsigned long PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PTRS_PER_PGD ; 
 int __create_hyp_mappings (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __phys_to_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hyp_pgd ; 
 scalar_t__ is_kernel_in_hyp_mode () ; 
 unsigned long kern_hyp_va (unsigned long) ; 
 int /*<<< orphan*/  kvm_kaddr_to_phys (void*) ; 

int create_hyp_mappings(void *from, void *to, pgprot_t prot)
{
	phys_addr_t phys_addr;
	unsigned long virt_addr;
	unsigned long start = kern_hyp_va((unsigned long)from);
	unsigned long end = kern_hyp_va((unsigned long)to);

	if (is_kernel_in_hyp_mode())
		return 0;

	start = start & PAGE_MASK;
	end = PAGE_ALIGN(end);

	for (virt_addr = start; virt_addr < end; virt_addr += PAGE_SIZE) {
		int err;

		phys_addr = kvm_kaddr_to_phys(from + virt_addr - start);
		err = __create_hyp_mappings(hyp_pgd, PTRS_PER_PGD,
					    virt_addr, virt_addr + PAGE_SIZE,
					    __phys_to_pfn(phys_addr),
					    prot);
		if (err)
			return err;
	}

	return 0;
}