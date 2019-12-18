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
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct kvm_vm {scalar_t__ mode; int pgd_created; int /*<<< orphan*/  pgd; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_GUEST_PAGE_TABLE_MIN_PADDR ; 
 int /*<<< orphan*/  TEST_ASSERT (int,char*,scalar_t__) ; 
 scalar_t__ VM_MODE_PXXV48_4K ; 
 int /*<<< orphan*/  vm_phy_page_alloc (struct kvm_vm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void virt_pgd_alloc(struct kvm_vm *vm, uint32_t pgd_memslot)
{
	TEST_ASSERT(vm->mode == VM_MODE_PXXV48_4K, "Attempt to use "
		"unknown or unsupported guest mode, mode: 0x%x", vm->mode);

	/* If needed, create page map l4 table. */
	if (!vm->pgd_created) {
		vm_paddr_t paddr = vm_phy_page_alloc(vm,
			KVM_GUEST_PAGE_TABLE_MIN_PADDR, pgd_memslot);
		vm->pgd = paddr;
		vm->pgd_created = true;
	}
}