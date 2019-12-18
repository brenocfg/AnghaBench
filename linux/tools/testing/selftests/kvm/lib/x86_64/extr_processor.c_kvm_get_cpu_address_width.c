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
struct kvm_cpuid_entry2 {int edx; int eax; } ;

/* Variables and functions */
 int kvm_get_cpuid_max () ; 
 struct kvm_cpuid_entry2* kvm_get_supported_cpuid_entry (int) ; 

void kvm_get_cpu_address_width(unsigned int *pa_bits, unsigned int *va_bits)
{
	struct kvm_cpuid_entry2 *entry;
	bool pae;

	/* SDM 4.1.4 */
	if (kvm_get_cpuid_max() < 0x80000008) {
		pae = kvm_get_supported_cpuid_entry(1)->edx & (1 << 6);
		*pa_bits = pae ? 36 : 32;
		*va_bits = 32;
	} else {
		entry = kvm_get_supported_cpuid_entry(0x80000008);
		*pa_bits = entry->eax & 0xff;
		*va_bits = (entry->eax >> 8) & 0xff;
	}
}