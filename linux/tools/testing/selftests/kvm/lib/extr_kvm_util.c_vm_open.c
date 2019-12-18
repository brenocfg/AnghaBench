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
struct kvm_vm {scalar_t__ kvm_fd; scalar_t__ fd; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  KSFT_SKIP ; 
 int /*<<< orphan*/  KVM_CAP_IMMEDIATE_EXIT ; 
 int /*<<< orphan*/  KVM_CREATE_VM ; 
 int /*<<< orphan*/  KVM_DEV_PATH ; 
 int /*<<< orphan*/  TEST_ASSERT (int,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ioctl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_check_cap (int /*<<< orphan*/ ) ; 
 scalar_t__ open (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void vm_open(struct kvm_vm *vm, int perm)
{
	vm->kvm_fd = open(KVM_DEV_PATH, perm);
	if (vm->kvm_fd < 0)
		exit(KSFT_SKIP);

	if (!kvm_check_cap(KVM_CAP_IMMEDIATE_EXIT)) {
		fprintf(stderr, "immediate_exit not available, skipping test\n");
		exit(KSFT_SKIP);
	}

	vm->fd = ioctl(vm->kvm_fd, KVM_CREATE_VM, vm->type);
	TEST_ASSERT(vm->fd >= 0, "KVM_CREATE_VM ioctl failed, "
		"rc: %i errno: %i", vm->fd, errno);
}