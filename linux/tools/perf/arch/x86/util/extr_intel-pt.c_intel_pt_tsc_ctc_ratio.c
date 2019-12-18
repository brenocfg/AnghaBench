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
typedef  unsigned int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  __get_cpuid (int,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static void intel_pt_tsc_ctc_ratio(u32 *n, u32 *d)
{
	unsigned int eax = 0, ebx = 0, ecx = 0, edx = 0;

	__get_cpuid(0x15, &eax, &ebx, &ecx, &edx);
	*n = ebx;
	*d = eax;
}