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

/* Variables and functions */
 int /*<<< orphan*/  KVM_CAP_MAX_VCPUS ; 
 int /*<<< orphan*/  KVM_CAP_MAX_VCPU_ID ; 
 int /*<<< orphan*/  TEST_ASSERT (int,char*,int,int) ; 
 int kvm_check_cap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  test_vcpu_creation (int,int) ; 

int main(int argc, char *argv[])
{
	int kvm_max_vcpu_id = kvm_check_cap(KVM_CAP_MAX_VCPU_ID);
	int kvm_max_vcpus = kvm_check_cap(KVM_CAP_MAX_VCPUS);

	printf("KVM_CAP_MAX_VCPU_ID: %d\n", kvm_max_vcpu_id);
	printf("KVM_CAP_MAX_VCPUS: %d\n", kvm_max_vcpus);

	/*
	 * Upstream KVM prior to 4.8 does not support KVM_CAP_MAX_VCPU_ID.
	 * Userspace is supposed to use KVM_CAP_MAX_VCPUS as the maximum ID
	 * in this case.
	 */
	if (!kvm_max_vcpu_id)
		kvm_max_vcpu_id = kvm_max_vcpus;

	TEST_ASSERT(kvm_max_vcpu_id >= kvm_max_vcpus,
		    "KVM_MAX_VCPU_ID (%d) must be at least as large as KVM_MAX_VCPUS (%d).",
		    kvm_max_vcpu_id, kvm_max_vcpus);

	test_vcpu_creation(0, kvm_max_vcpus);

	if (kvm_max_vcpu_id > kvm_max_vcpus)
		test_vcpu_creation(
			kvm_max_vcpu_id - kvm_max_vcpus, kvm_max_vcpus);

	return 0;
}