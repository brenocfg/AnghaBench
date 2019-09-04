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

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT (int,char*,unsigned long,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int ioctl (int /*<<< orphan*/ ,unsigned long,void*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

void vm_ioctl(struct kvm_vm *vm, unsigned long cmd, void *arg)
{
	int ret;

	ret = ioctl(vm->fd, cmd, arg);
	TEST_ASSERT(ret == 0, "vm ioctl %lu failed, rc: %i errno: %i (%s)",
		cmd, ret, errno, strerror(errno));
}