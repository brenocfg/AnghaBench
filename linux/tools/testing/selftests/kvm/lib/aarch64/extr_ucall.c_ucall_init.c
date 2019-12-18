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
typedef  int vm_paddr_t ;
struct kvm_vm {int va_bits; unsigned int pa_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT (int,char*,...) ; 
 int ucall_mmio_init (struct kvm_vm*,int) ; 

void ucall_init(struct kvm_vm *vm, void *arg)
{
	vm_paddr_t gpa, start, end, step, offset;
	unsigned int bits;
	bool ret;

	if (arg) {
		gpa = (vm_paddr_t)arg;
		ret = ucall_mmio_init(vm, gpa);
		TEST_ASSERT(ret, "Can't set ucall mmio address to %lx", gpa);
		return;
	}

	/*
	 * Find an address within the allowed physical and virtual address
	 * spaces, that does _not_ have a KVM memory region associated with
	 * it. Identity mapping an address like this allows the guest to
	 * access it, but as KVM doesn't know what to do with it, it
	 * will assume it's something userspace handles and exit with
	 * KVM_EXIT_MMIO. Well, at least that's how it works for AArch64.
	 * Here we start with a guess that the addresses around 5/8th
	 * of the allowed space are unmapped and then work both down and
	 * up from there in 1/16th allowed space sized steps.
	 *
	 * Note, we need to use VA-bits - 1 when calculating the allowed
	 * virtual address space for an identity mapping because the upper
	 * half of the virtual address space is the two's complement of the
	 * lower and won't match physical addresses.
	 */
	bits = vm->va_bits - 1;
	bits = vm->pa_bits < bits ? vm->pa_bits : bits;
	end = 1ul << bits;
	start = end * 5 / 8;
	step = end / 16;
	for (offset = 0; offset < end - start; offset += step) {
		if (ucall_mmio_init(vm, start - offset))
			return;
		if (ucall_mmio_init(vm, start + offset))
			return;
	}
	TEST_ASSERT(false, "Can't find a ucall mmio address");
}