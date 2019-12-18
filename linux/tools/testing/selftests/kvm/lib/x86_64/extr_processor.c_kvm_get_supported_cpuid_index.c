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
struct kvm_cpuid_entry2 {scalar_t__ function; scalar_t__ index; } ;
struct kvm_cpuid2 {int nent; struct kvm_cpuid_entry2* entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT (struct kvm_cpuid_entry2*,char*,scalar_t__,scalar_t__) ; 
 struct kvm_cpuid2* kvm_get_supported_cpuid () ; 

struct kvm_cpuid_entry2 *
kvm_get_supported_cpuid_index(uint32_t function, uint32_t index)
{
	struct kvm_cpuid2 *cpuid;
	struct kvm_cpuid_entry2 *entry = NULL;
	int i;

	cpuid = kvm_get_supported_cpuid();
	for (i = 0; i < cpuid->nent; i++) {
		if (cpuid->entries[i].function == function &&
		    cpuid->entries[i].index == index) {
			entry = &cpuid->entries[i];
			break;
		}
	}

	TEST_ASSERT(entry, "Guest CPUID entry not found: (EAX=%x, ECX=%x).",
		    function, index);
	return entry;
}