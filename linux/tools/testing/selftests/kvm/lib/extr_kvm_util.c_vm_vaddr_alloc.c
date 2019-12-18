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
typedef  int vm_vaddr_t ;
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct kvm_vm {size_t page_shift; size_t page_size; int /*<<< orphan*/  vpages_mapped; } ;

/* Variables and functions */
 int KVM_UTIL_MIN_PFN ; 
 int /*<<< orphan*/  sparsebit_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  virt_pg_map (struct kvm_vm*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_pgd_alloc (struct kvm_vm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_phy_page_alloc (struct kvm_vm*,int,int /*<<< orphan*/ ) ; 
 int vm_vaddr_unused_gap (struct kvm_vm*,size_t,int) ; 

vm_vaddr_t vm_vaddr_alloc(struct kvm_vm *vm, size_t sz, vm_vaddr_t vaddr_min,
			  uint32_t data_memslot, uint32_t pgd_memslot)
{
	uint64_t pages = (sz >> vm->page_shift) + ((sz % vm->page_size) != 0);

	virt_pgd_alloc(vm, pgd_memslot);

	/*
	 * Find an unused range of virtual page addresses of at least
	 * pages in length.
	 */
	vm_vaddr_t vaddr_start = vm_vaddr_unused_gap(vm, sz, vaddr_min);

	/* Map the virtual pages. */
	for (vm_vaddr_t vaddr = vaddr_start; pages > 0;
		pages--, vaddr += vm->page_size) {
		vm_paddr_t paddr;

		paddr = vm_phy_page_alloc(vm,
				KVM_UTIL_MIN_PFN * vm->page_size, data_memslot);

		virt_pg_map(vm, vaddr, paddr, pgd_memslot);

		sparsebit_set(vm->vpages_mapped,
			vaddr >> vm->page_shift);
	}

	return vaddr_start;
}