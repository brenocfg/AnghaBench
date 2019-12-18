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
struct kvm_cpuid_entry2 {int dummy; } ;
struct kvm_cpuid2 {int nent; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_GET_SUPPORTED_HV_CPUID ; 
 int /*<<< orphan*/  VCPU_ID ; 
 int /*<<< orphan*/  abort () ; 
 struct kvm_cpuid2* malloc (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  vcpu_ioctl (struct kvm_vm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kvm_cpuid2*) ; 

struct kvm_cpuid2 *kvm_get_supported_hv_cpuid(struct kvm_vm *vm)
{
	int nent = 20; /* should be enough */
	static struct kvm_cpuid2 *cpuid;

	cpuid = malloc(sizeof(*cpuid) + nent * sizeof(struct kvm_cpuid_entry2));

	if (!cpuid) {
		perror("malloc");
		abort();
	}

	cpuid->nent = nent;

	vcpu_ioctl(vm, VCPU_ID, KVM_GET_SUPPORTED_HV_CPUID, cpuid);

	return cpuid;
}