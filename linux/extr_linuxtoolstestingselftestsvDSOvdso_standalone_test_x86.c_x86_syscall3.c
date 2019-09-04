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

__attribute__((used)) static inline long x86_syscall3(long nr, long a0, long a1, long a2)
{
	long ret;
#ifdef __x86_64__
	asm volatile ("syscall" : "=a" (ret) : "a" (nr),
		      "D" (a0), "S" (a1), "d" (a2) :
		      "cc", "memory", "rcx",
		      "r8", "r9", "r10", "r11" );
#else
	asm volatile ("int $0x80" : "=a" (ret) : "a" (nr),
		      "b" (a0), "c" (a1), "d" (a2) :
		      "cc", "memory" );
#endif
	return ret;
}