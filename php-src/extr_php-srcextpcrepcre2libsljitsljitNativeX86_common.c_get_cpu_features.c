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
typedef  int sljit_u32 ;

/* Variables and functions */
 int cpu_has_cmov ; 

__attribute__((used)) static void get_cpu_features(void)
{
	sljit_u32 features;

#if defined(_MSC_VER) && _MSC_VER >= 1400

	int CPUInfo[4];
	__cpuid(CPUInfo, 1);
	features = (sljit_u32)CPUInfo[3];

#elif defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__SUNPRO_C)

	/* AT&T syntax. */
	__asm__ (
		"movl $0x1, %%eax\n"
#if (defined SLJIT_CONFIG_X86_32 && SLJIT_CONFIG_X86_32)
		/* On x86-32, there is no red zone, so this
		   should work (no need for a local variable). */
		"push %%ebx\n"
#endif
		"cpuid\n"
#if (defined SLJIT_CONFIG_X86_32 && SLJIT_CONFIG_X86_32)
		"pop %%ebx\n"
#endif
		"movl %%edx, %0\n"
		: "=g" (features)
		:
#if (defined SLJIT_CONFIG_X86_32 && SLJIT_CONFIG_X86_32)
		: "%eax", "%ecx", "%edx"
#else
		: "%rax", "%rbx", "%rcx", "%rdx"
#endif
	);

#else /* _MSC_VER && _MSC_VER >= 1400 */

	/* Intel syntax. */
	__asm {
		mov eax, 1
		cpuid
		mov features, edx
	}

#endif /* _MSC_VER && _MSC_VER >= 1400 */

#if (defined SLJIT_DETECT_SSE2 && SLJIT_DETECT_SSE2)
	cpu_has_sse2 = (features >> 26) & 0x1;
#endif
	cpu_has_cmov = (features >> 15) & 0x1;
}