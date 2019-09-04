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
typedef  scalar_t__ uint32_t ;
struct vcpu {scalar_t__ id; struct vcpu* next; } ;
struct kvm_vm {struct vcpu* vcpu_head; } ;

/* Variables and functions */

struct vcpu *vcpu_find(struct kvm_vm *vm,
	uint32_t vcpuid)
{
	struct vcpu *vcpup;

	for (vcpup = vm->vcpu_head; vcpup; vcpup = vcpup->next) {
		if (vcpup->id == vcpuid)
			return vcpup;
	}

	return NULL;
}