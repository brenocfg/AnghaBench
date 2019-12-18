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
typedef  int uint32_t ;
struct vcpu {int id; scalar_t__ fd; struct vcpu* next; struct vcpu* prev; struct kvm_run* state; } ;
struct kvm_vm {struct vcpu* vcpu_head; int /*<<< orphan*/  fd; } ;
struct kvm_run {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_CREATE_VCPU ; 
 struct kvm_run* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  TEST_ASSERT (int,char*,...) ; 
 struct vcpu* calloc (int,int) ; 
 int errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mmap (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct vcpu* vcpu_find (struct kvm_vm*,int) ; 
 int vcpu_mmap_sz () ; 

void vm_vcpu_add(struct kvm_vm *vm, uint32_t vcpuid)
{
	struct vcpu *vcpu;

	/* Confirm a vcpu with the specified id doesn't already exist. */
	vcpu = vcpu_find(vm, vcpuid);
	if (vcpu != NULL)
		TEST_ASSERT(false, "vcpu with the specified id "
			"already exists,\n"
			"  requested vcpuid: %u\n"
			"  existing vcpuid: %u state: %p",
			vcpuid, vcpu->id, vcpu->state);

	/* Allocate and initialize new vcpu structure. */
	vcpu = calloc(1, sizeof(*vcpu));
	TEST_ASSERT(vcpu != NULL, "Insufficient Memory");
	vcpu->id = vcpuid;
	vcpu->fd = ioctl(vm->fd, KVM_CREATE_VCPU, vcpuid);
	TEST_ASSERT(vcpu->fd >= 0, "KVM_CREATE_VCPU failed, rc: %i errno: %i",
		vcpu->fd, errno);

	TEST_ASSERT(vcpu_mmap_sz() >= sizeof(*vcpu->state), "vcpu mmap size "
		"smaller than expected, vcpu_mmap_sz: %i expected_min: %zi",
		vcpu_mmap_sz(), sizeof(*vcpu->state));
	vcpu->state = (struct kvm_run *) mmap(NULL, sizeof(*vcpu->state),
		PROT_READ | PROT_WRITE, MAP_SHARED, vcpu->fd, 0);
	TEST_ASSERT(vcpu->state != MAP_FAILED, "mmap vcpu_state failed, "
		"vcpu id: %u errno: %i", vcpuid, errno);

	/* Add to linked-list of VCPUs. */
	if (vm->vcpu_head)
		vm->vcpu_head->prev = vcpu;
	vcpu->next = vm->vcpu_head;
	vm->vcpu_head = vcpu;
}