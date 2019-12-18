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
struct kvm_cpuid_entry2 {int ecx; } ;

/* Variables and functions */
 int CPUID_VMX ; 
 int /*<<< orphan*/  KSFT_SKIP ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 struct kvm_cpuid_entry2* kvm_get_supported_cpuid_entry (int) ; 
 int /*<<< orphan*/  stderr ; 

void nested_vmx_check_supported(void)
{
	struct kvm_cpuid_entry2 *entry = kvm_get_supported_cpuid_entry(1);

	if (!(entry->ecx & CPUID_VMX)) {
		fprintf(stderr, "nested VMX not enabled, skipping test\n");
		exit(KSFT_SKIP);
	}
}