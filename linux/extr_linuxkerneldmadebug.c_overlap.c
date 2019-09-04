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

__attribute__((used)) static inline bool overlap(void *addr, unsigned long len, void *start, void *end)
{
	unsigned long a1 = (unsigned long)addr;
	unsigned long b1 = a1 + len;
	unsigned long a2 = (unsigned long)start;
	unsigned long b2 = (unsigned long)end;

	return !(b1 <= a2 || a1 >= b2);
}