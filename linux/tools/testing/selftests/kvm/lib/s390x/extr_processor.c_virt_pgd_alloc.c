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
struct kvm_vm {int page_size; int pgd_created; int /*<<< orphan*/  pgd; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_GUEST_PAGE_TABLE_MIN_PADDR ; 
 int PAGES_PER_REGION ; 
 int /*<<< orphan*/  TEST_ASSERT (int,char*,int) ; 
 int /*<<< orphan*/  addr_gpa2hva (struct kvm_vm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  vm_phy_pages_alloc (struct kvm_vm*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void virt_pgd_alloc(struct kvm_vm *vm, uint32_t memslot)
{
	vm_paddr_t paddr;

	TEST_ASSERT(vm->page_size == 4096, "Unsupported page size: 0x%x",
		    vm->page_size);

	if (vm->pgd_created)
		return;

	paddr = vm_phy_pages_alloc(vm, PAGES_PER_REGION,
				   KVM_GUEST_PAGE_TABLE_MIN_PADDR, memslot);
	memset(addr_gpa2hva(vm, paddr), 0xff, PAGES_PER_REGION * vm->page_size);

	vm->pgd = paddr;
	vm->pgd_created = true;
}