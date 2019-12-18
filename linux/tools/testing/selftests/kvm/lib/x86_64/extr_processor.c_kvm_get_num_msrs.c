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
struct kvm_vm {int /*<<< orphan*/  kvm_fd; } ;
struct kvm_msr_list {int nmsrs; } ;

/* Variables and functions */
 scalar_t__ E2BIG ; 
 int /*<<< orphan*/  KVM_GET_MSR_INDEX_LIST ; 
 int /*<<< orphan*/  TEST_ASSERT (int,char*,int) ; 
 scalar_t__ errno ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kvm_msr_list*) ; 

__attribute__((used)) static int kvm_get_num_msrs(struct kvm_vm *vm)
{
	struct kvm_msr_list nmsrs;
	int r;

	nmsrs.nmsrs = 0;
	r = ioctl(vm->kvm_fd, KVM_GET_MSR_INDEX_LIST, &nmsrs);
	TEST_ASSERT(r == -1 && errno == E2BIG, "Unexpected result from KVM_GET_MSR_INDEX_LIST probe, r: %i",
		r);

	return nmsrs.nmsrs;
}