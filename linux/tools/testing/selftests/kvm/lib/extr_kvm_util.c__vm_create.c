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
struct kvm_vm {int mode; int pgtable_levels; int pa_bits; int va_bits; int page_size; int page_shift; unsigned long long max_gfn; void* vpages_mapped; void* vpages_valid; scalar_t__ type; } ;
typedef  enum vm_guest_mode { ____Placeholder_vm_guest_mode } vm_guest_mode ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*,int) ; 
 scalar_t__ KVM_VM_TYPE_ARM_IPA_SIZE (int) ; 
 int /*<<< orphan*/  TEST_ASSERT (int,char*,...) ; 
 int /*<<< orphan*/  VM_MEM_SRC_ANONYMOUS ; 
#define  VM_MODE_P40V48_4K 134 
#define  VM_MODE_P40V48_64K 133 
#define  VM_MODE_P48V48_4K 132 
#define  VM_MODE_P48V48_64K 131 
#define  VM_MODE_P52V48_4K 130 
#define  VM_MODE_P52V48_64K 129 
#define  VM_MODE_PXXV48_4K 128 
 struct kvm_vm* calloc (int,int) ; 
 int /*<<< orphan*/  kvm_get_cpu_address_width (int*,int*) ; 
 void* sparsebit_alloc () ; 
 int /*<<< orphan*/  sparsebit_set_num (void*,unsigned long long,unsigned long long) ; 
 int vm_guest_mode_string (int) ; 
 int /*<<< orphan*/  vm_open (struct kvm_vm*,int) ; 
 int /*<<< orphan*/  vm_userspace_mem_region_add (struct kvm_vm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

struct kvm_vm *_vm_create(enum vm_guest_mode mode, uint64_t phy_pages, int perm)
{
	struct kvm_vm *vm;

	DEBUG("Testing guest mode: %s\n", vm_guest_mode_string(mode));

	vm = calloc(1, sizeof(*vm));
	TEST_ASSERT(vm != NULL, "Insufficient Memory");

	vm->mode = mode;
	vm->type = 0;

	/* Setup mode specific traits. */
	switch (vm->mode) {
	case VM_MODE_P52V48_4K:
		vm->pgtable_levels = 4;
		vm->pa_bits = 52;
		vm->va_bits = 48;
		vm->page_size = 0x1000;
		vm->page_shift = 12;
		break;
	case VM_MODE_P52V48_64K:
		vm->pgtable_levels = 3;
		vm->pa_bits = 52;
		vm->va_bits = 48;
		vm->page_size = 0x10000;
		vm->page_shift = 16;
		break;
	case VM_MODE_P48V48_4K:
		vm->pgtable_levels = 4;
		vm->pa_bits = 48;
		vm->va_bits = 48;
		vm->page_size = 0x1000;
		vm->page_shift = 12;
		break;
	case VM_MODE_P48V48_64K:
		vm->pgtable_levels = 3;
		vm->pa_bits = 48;
		vm->va_bits = 48;
		vm->page_size = 0x10000;
		vm->page_shift = 16;
		break;
	case VM_MODE_P40V48_4K:
		vm->pgtable_levels = 4;
		vm->pa_bits = 40;
		vm->va_bits = 48;
		vm->page_size = 0x1000;
		vm->page_shift = 12;
		break;
	case VM_MODE_P40V48_64K:
		vm->pgtable_levels = 3;
		vm->pa_bits = 40;
		vm->va_bits = 48;
		vm->page_size = 0x10000;
		vm->page_shift = 16;
		break;
	case VM_MODE_PXXV48_4K:
#ifdef __x86_64__
		kvm_get_cpu_address_width(&vm->pa_bits, &vm->va_bits);
		TEST_ASSERT(vm->va_bits == 48, "Linear address width "
			    "(%d bits) not supported", vm->va_bits);
		vm->pgtable_levels = 4;
		vm->page_size = 0x1000;
		vm->page_shift = 12;
		DEBUG("Guest physical address width detected: %d\n",
		      vm->pa_bits);
#else
		TEST_ASSERT(false, "VM_MODE_PXXV48_4K not supported on "
			    "non-x86 platforms");
#endif
		break;
	default:
		TEST_ASSERT(false, "Unknown guest mode, mode: 0x%x", mode);
	}

#ifdef __aarch64__
	if (vm->pa_bits != 40)
		vm->type = KVM_VM_TYPE_ARM_IPA_SIZE(vm->pa_bits);
#endif

	vm_open(vm, perm);

	/* Limit to VA-bit canonical virtual addresses. */
	vm->vpages_valid = sparsebit_alloc();
	sparsebit_set_num(vm->vpages_valid,
		0, (1ULL << (vm->va_bits - 1)) >> vm->page_shift);
	sparsebit_set_num(vm->vpages_valid,
		(~((1ULL << (vm->va_bits - 1)) - 1)) >> vm->page_shift,
		(1ULL << (vm->va_bits - 1)) >> vm->page_shift);

	/* Limit physical addresses to PA-bits. */
	vm->max_gfn = ((1ULL << vm->pa_bits) >> vm->page_shift) - 1;

	/* Allocate and setup memory for guest. */
	vm->vpages_mapped = sparsebit_alloc();
	if (phy_pages != 0)
		vm_userspace_mem_region_add(vm, VM_MEM_SRC_ANONYMOUS,
					    0, 0, phy_pages, 0);

	return vm;
}