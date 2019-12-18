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
struct kvm_sregs {int apic_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT (int,char*,int) ; 
 int /*<<< orphan*/  VCPU_ID ; 
 int _vcpu_sregs_set (struct kvm_vm*,int /*<<< orphan*/ ,struct kvm_sregs*) ; 
 int /*<<< orphan*/  kvm_vm_free (struct kvm_vm*) ; 
 int /*<<< orphan*/  setbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  vcpu_sregs_get (struct kvm_vm*,int /*<<< orphan*/ ,struct kvm_sregs*) ; 
 struct kvm_vm* vm_create_default (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int main(int argc, char *argv[])
{
	struct kvm_sregs sregs;
	struct kvm_vm *vm;
	int rc;

	/* Tell stdout not to buffer its content */
	setbuf(stdout, NULL);

	/* Create VM */
	vm = vm_create_default(VCPU_ID, 0, NULL);

	vcpu_sregs_get(vm, VCPU_ID, &sregs);
	sregs.apic_base = 1 << 10;
	rc = _vcpu_sregs_set(vm, VCPU_ID, &sregs);
	TEST_ASSERT(rc, "Set IA32_APIC_BASE to %llx (invalid)",
		    sregs.apic_base);
	sregs.apic_base = 1 << 11;
	rc = _vcpu_sregs_set(vm, VCPU_ID, &sregs);
	TEST_ASSERT(!rc, "Couldn't set IA32_APIC_BASE to %llx (valid)",
		    sregs.apic_base);

	kvm_vm_free(vm);

	return 0;
}