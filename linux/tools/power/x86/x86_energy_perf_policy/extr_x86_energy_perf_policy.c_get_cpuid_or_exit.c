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
 int /*<<< orphan*/  __get_cpuid (unsigned int,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 

__attribute__((used)) static void get_cpuid_or_exit(unsigned int leaf,
			     unsigned int *eax, unsigned int *ebx,
			     unsigned int *ecx, unsigned int *edx)
{
	if (!__get_cpuid(leaf, eax, ebx, ecx, edx))
		errx(1, "Processor not supported\n");
}