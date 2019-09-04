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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct vcpu {int /*<<< orphan*/  fd; } ;
struct kvm_vm {int dummy; } ;
struct kvm_msrs {int nmsrs; } ;
struct kvm_msr_entry {int /*<<< orphan*/  data; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_GET_MSRS ; 
 int /*<<< orphan*/  TEST_ASSERT (int,char*,int,...) ; 
 int /*<<< orphan*/  errno ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kvm_msrs*) ; 
 struct vcpu* vcpu_find (struct kvm_vm*,int /*<<< orphan*/ ) ; 

uint64_t vcpu_get_msr(struct kvm_vm *vm, uint32_t vcpuid, uint64_t msr_index)
{
	struct vcpu *vcpu = vcpu_find(vm, vcpuid);
	struct {
		struct kvm_msrs header;
		struct kvm_msr_entry entry;
	} buffer = {};
	int r;

	TEST_ASSERT(vcpu != NULL, "vcpu not found, vcpuid: %u", vcpuid);
	buffer.header.nmsrs = 1;
	buffer.entry.index = msr_index;
	r = ioctl(vcpu->fd, KVM_GET_MSRS, &buffer.header);
	TEST_ASSERT(r == 1, "KVM_GET_MSRS IOCTL failed,\n"
		"  rc: %i errno: %i", r, errno);

	return buffer.entry.data;
}