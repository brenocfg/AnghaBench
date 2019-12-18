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
typedef  int /*<<< orphan*/  uint32_t ;
struct kvm_vm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT (int,char*,unsigned long,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _vcpu_ioctl (struct kvm_vm*,int /*<<< orphan*/ ,unsigned long,void*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

void vcpu_ioctl(struct kvm_vm *vm, uint32_t vcpuid,
		unsigned long cmd, void *arg)
{
	int ret;

	ret = _vcpu_ioctl(vm, vcpuid, cmd, arg);
	TEST_ASSERT(ret == 0, "vcpu ioctl %lu failed, rc: %i errno: %i (%s)",
		cmd, ret, errno, strerror(errno));
}