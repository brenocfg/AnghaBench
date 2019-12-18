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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static inline int boot_cpu_has(int flag)
{
	u32 eax, ebx, ecx, edx;

	eax = (flag & 0x100) ? 7 :
		(flag & 0x20) ? 0x80000001 : 1;
	ecx = 0;

	asm volatile("cpuid"
		     : "+a" (eax), "=b" (ebx), "=d" (edx), "+c" (ecx));

	return ((flag & 0x100 ? ebx :
		(flag & 0x80) ? ecx : edx) >> (flag & 31)) & 1;
}