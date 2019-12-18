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
struct kvm_vm {int /*<<< orphan*/  fd; } ;
struct kvm_enable_cap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_ENABLE_CAP ; 
 int /*<<< orphan*/  TEST_ASSERT (int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kvm_enable_cap*) ; 

int vm_enable_cap(struct kvm_vm *vm, struct kvm_enable_cap *cap)
{
	int ret;

	ret = ioctl(vm->fd, KVM_ENABLE_CAP, cap);
	TEST_ASSERT(ret == 0, "KVM_ENABLE_CAP IOCTL failed,\n"
		"  rc: %i errno: %i", ret, errno);

	return ret;
}