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
typedef  scalar_t__ uint64_t ;
struct kvm_vm {int mode; int page_size; int page_shift; unsigned long long max_gfn; void* vpages_mapped; void* vpages_valid; } ;
typedef  enum vm_guest_mode { ____Placeholder_vm_guest_mode } vm_guest_mode ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT (int,char*,...) ; 
 int /*<<< orphan*/  VM_MEM_SRC_ANONYMOUS ; 
#define  VM_MODE_FLAT48PG 128 
 struct kvm_vm* calloc (int,int) ; 
 void* sparsebit_alloc () ; 
 int /*<<< orphan*/  sparsebit_set_num (void*,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  vm_open (struct kvm_vm*,int) ; 
 int /*<<< orphan*/  vm_userspace_mem_region_add (struct kvm_vm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

struct kvm_vm *vm_create(enum vm_guest_mode mode, uint64_t phy_pages, int perm)
{
	struct kvm_vm *vm;
	int kvm_fd;

	/* Allocate memory. */
	vm = calloc(1, sizeof(*vm));
	TEST_ASSERT(vm != NULL, "Insufficent Memory");

	vm->mode = mode;
	vm_open(vm, perm);

	/* Setup mode specific traits. */
	switch (vm->mode) {
	case VM_MODE_FLAT48PG:
		vm->page_size = 0x1000;
		vm->page_shift = 12;

		/* Limit to 48-bit canonical virtual addresses. */
		vm->vpages_valid = sparsebit_alloc();
		sparsebit_set_num(vm->vpages_valid,
			0, (1ULL << (48 - 1)) >> vm->page_shift);
		sparsebit_set_num(vm->vpages_valid,
			(~((1ULL << (48 - 1)) - 1)) >> vm->page_shift,
			(1ULL << (48 - 1)) >> vm->page_shift);

		/* Limit physical addresses to 52-bits. */
		vm->max_gfn = ((1ULL << 52) >> vm->page_shift) - 1;
		break;

	default:
		TEST_ASSERT(false, "Unknown guest mode, mode: 0x%x", mode);
	}

	/* Allocate and setup memory for guest. */
	vm->vpages_mapped = sparsebit_alloc();
	if (phy_pages != 0)
		vm_userspace_mem_region_add(vm, VM_MEM_SRC_ANONYMOUS,
					    0, 0, phy_pages, 0);

	return vm;
}