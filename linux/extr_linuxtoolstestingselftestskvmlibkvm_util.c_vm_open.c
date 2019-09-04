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
struct kvm_vm {scalar_t__ kvm_fd; scalar_t__ fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  KSFT_SKIP ; 
 int /*<<< orphan*/  KVM_CREATE_VM ; 
 int /*<<< orphan*/  KVM_DEV_PATH ; 
 int /*<<< orphan*/  TEST_ASSERT (int,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ ioctl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ open (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vm_open(struct kvm_vm *vm, int perm)
{
	vm->kvm_fd = open(KVM_DEV_PATH, perm);
	if (vm->kvm_fd < 0)
		exit(KSFT_SKIP);

	/* Create VM. */
	vm->fd = ioctl(vm->kvm_fd, KVM_CREATE_VM, NULL);
	TEST_ASSERT(vm->fd >= 0, "KVM_CREATE_VM ioctl failed, "
		"rc: %i errno: %i", vm->fd, errno);
}