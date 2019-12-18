#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct kvm_vm {int /*<<< orphan*/  kvm_fd; int /*<<< orphan*/  fd; TYPE_1__* vcpu_head; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT (int,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  vm_vcpu_rm (struct kvm_vm*,int /*<<< orphan*/ ) ; 

void kvm_vm_release(struct kvm_vm *vmp)
{
	int ret;

	while (vmp->vcpu_head)
		vm_vcpu_rm(vmp, vmp->vcpu_head->id);

	ret = close(vmp->fd);
	TEST_ASSERT(ret == 0, "Close of vm fd failed,\n"
		"  vmp->fd: %i rc: %i errno: %i", vmp->fd, ret, errno);

	close(vmp->kvm_fd);
	TEST_ASSERT(ret == 0, "Close of /dev/kvm fd failed,\n"
		"  vmp->kvm_fd: %i rc: %i errno: %i", vmp->kvm_fd, ret, errno);
}