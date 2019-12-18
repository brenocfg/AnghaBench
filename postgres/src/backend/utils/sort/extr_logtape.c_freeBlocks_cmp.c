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

__attribute__((used)) static int
freeBlocks_cmp(const void *a, const void *b)
{
	long		ablk = *((const long *) a);
	long		bblk = *((const long *) b);

	/* can't just subtract because long might be wider than int */
	if (ablk < bblk)
		return 1;
	if (ablk > bblk)
		return -1;
	return 0;
}