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
typedef  size_t uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct vmx_pages {int dummy; } ;
struct kvm_vm {size_t page_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT (int,char*) ; 
 int /*<<< orphan*/  nested_pg_map (struct vmx_pages*,struct kvm_vm*,size_t,size_t,int /*<<< orphan*/ ) ; 

void nested_map(struct vmx_pages *vmx, struct kvm_vm *vm,
		uint64_t nested_paddr, uint64_t paddr, uint64_t size,
		uint32_t eptp_memslot)
{
	size_t page_size = vm->page_size;
	size_t npages = size / page_size;

	TEST_ASSERT(nested_paddr + size > nested_paddr, "Vaddr overflow");
	TEST_ASSERT(paddr + size > paddr, "Paddr overflow");

	while (npages--) {
		nested_pg_map(vmx, vm, nested_paddr, paddr, eptp_memslot);
		nested_paddr += page_size;
		paddr += page_size;
	}
}