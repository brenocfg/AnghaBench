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
struct kvm_vm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_GUEST_PHY_PAGES ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  VM_MODE_DEFAULT ; 
 int /*<<< orphan*/  kvm_vm_free (struct kvm_vm*) ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 
 struct kvm_vm* vm_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_vcpu_add (struct kvm_vm*,int) ; 

void test_vcpu_creation(int first_vcpu_id, int num_vcpus)
{
	struct kvm_vm *vm;
	int i;

	printf("Testing creating %d vCPUs, with IDs %d...%d.\n",
	       num_vcpus, first_vcpu_id, first_vcpu_id + num_vcpus - 1);

	vm = vm_create(VM_MODE_DEFAULT, DEFAULT_GUEST_PHY_PAGES, O_RDWR);

	for (i = 0; i < num_vcpus; i++) {
		int vcpu_id = first_vcpu_id + i;

		/* This asserts that the vCPU was created. */
		vm_vcpu_add(vm, vcpu_id);
	}

	kvm_vm_free(vm);
}