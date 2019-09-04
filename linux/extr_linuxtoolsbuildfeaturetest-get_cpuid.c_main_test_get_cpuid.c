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
 int __get_cpuid (int,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 

int main(void)
{
	unsigned int eax = 0, ebx = 0, ecx = 0, edx = 0;
	return __get_cpuid(0x15, &eax, &ebx, &ecx, &edx);
}