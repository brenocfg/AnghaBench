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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct kvm_vm {int dummy; } ;

/* Variables and functions */
 int DEFAULT_GUEST_PHY_PAGES ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  VM_MODE_DEFAULT ; 
 int /*<<< orphan*/  kvm_vm_elf_load (struct kvm_vm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  program_invocation_name ; 
 struct kvm_vm* vm_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_vcpu_add_default (struct kvm_vm*,int /*<<< orphan*/ ,void*) ; 

struct kvm_vm *vm_create_default(uint32_t vcpuid, uint64_t extra_mem_pages,
				 void *guest_code)
{
	/*
	 * The additional amount of pages required for the page tables is:
	 * 1 * n / 256 + 4 * (n / 256) / 2048 + 4 * (n / 256) / 2048^2 + ...
	 * which is definitely smaller than (n / 256) * 2.
	 */
	uint64_t extra_pg_pages = extra_mem_pages / 256 * 2;
	struct kvm_vm *vm;

	vm = vm_create(VM_MODE_DEFAULT,
		       DEFAULT_GUEST_PHY_PAGES + extra_pg_pages, O_RDWR);

	kvm_vm_elf_load(vm, program_invocation_name, 0, 0);
	vm_vcpu_add_default(vm, vcpuid, guest_code);

	return vm;
}