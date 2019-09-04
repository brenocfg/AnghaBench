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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int X86_CR4_OSXSAVE ; 
 int X86_FEATURE_OSXSAVE ; 
 int get_cr4 () ; 

__attribute__((used)) static inline bool cr4_cpuid_is_sync(void)
{
	int func, subfunc;
	uint32_t eax, ebx, ecx, edx;
	uint64_t cr4;

	func = 0x1;
	subfunc = 0x0;
	__asm__ __volatile__("cpuid"
			     : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
			     : "a"(func), "c"(subfunc));

	cr4 = get_cr4();

	return (!!(ecx & X86_FEATURE_OSXSAVE)) == (!!(cr4 & X86_CR4_OSXSAVE));
}