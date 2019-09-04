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
struct kvm_enable_cap {int* args; scalar_t__ flags; int /*<<< orphan*/  cap; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_CAP_MSR_PLATFORM_INFO ; 
 int /*<<< orphan*/  vm_enable_cap (struct kvm_vm*,struct kvm_enable_cap*) ; 

__attribute__((used)) static void set_msr_platform_info_enabled(struct kvm_vm *vm, bool enable)
{
	struct kvm_enable_cap cap = {};

	cap.cap = KVM_CAP_MSR_PLATFORM_INFO;
	cap.flags = 0;
	cap.args[0] = (int)enable;
	vm_enable_cap(vm, &cap);
}