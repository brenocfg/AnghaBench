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
typedef  scalar_t__ vm_vaddr_t ;
struct kvm_vm {uintptr_t page_shift; uintptr_t page_size; } ;

/* Variables and functions */
 scalar_t__ addr_gva2hva (struct kvm_vm*,scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 int memcmp (void*,void*,size_t) ; 

int kvm_memcmp_hva_gva(void *hva, struct kvm_vm *vm, vm_vaddr_t gva, size_t len)
{
	size_t amt;

	/*
	 * Compare a batch of bytes until either a match is found
	 * or all the bytes have been compared.
	 */
	for (uintptr_t offset = 0; offset < len; offset += amt) {
		uintptr_t ptr1 = (uintptr_t)hva + offset;

		/*
		 * Determine host address for guest virtual address
		 * at offset.
		 */
		uintptr_t ptr2 = (uintptr_t)addr_gva2hva(vm, gva + offset);

		/*
		 * Determine amount to compare on this pass.
		 * Don't allow the comparsion to cross a page boundary.
		 */
		amt = len - offset;
		if ((ptr1 >> vm->page_shift) != ((ptr1 + amt) >> vm->page_shift))
			amt = vm->page_size - (ptr1 % vm->page_size);
		if ((ptr2 >> vm->page_shift) != ((ptr2 + amt) >> vm->page_shift))
			amt = vm->page_size - (ptr2 % vm->page_size);

		assert((ptr1 >> vm->page_shift) == ((ptr1 + amt - 1) >> vm->page_shift));
		assert((ptr2 >> vm->page_shift) == ((ptr2 + amt - 1) >> vm->page_shift));

		/*
		 * Perform the comparison.  If there is a difference
		 * return that result to the caller, otherwise need
		 * to continue on looking for a mismatch.
		 */
		int ret = memcmp((void *)ptr1, (void *)ptr2, amt);
		if (ret != 0)
			return ret;
	}

	/*
	 * No mismatch found.  Let the caller know the two memory
	 * areas are equal.
	 */
	return 0;
}