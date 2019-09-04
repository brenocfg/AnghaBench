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
typedef  scalar_t__ pid_t ;

/* Variables and functions */

__attribute__((used)) static int pidlist_uniq(pid_t *list, int length)
{
	int src, dest = 1;

	/*
	 * we presume the 0th element is unique, so i starts at 1. trivial
	 * edge cases first; no work needs to be done for either
	 */
	if (length == 0 || length == 1)
		return length;
	/* src and dest walk down the list; dest counts unique elements */
	for (src = 1; src < length; src++) {
		/* find next unique element */
		while (list[src] == list[src-1]) {
			src++;
			if (src == length)
				goto after;
		}
		/* dest always points to where the next unique element goes */
		list[dest] = list[src];
		dest++;
	}
after:
	return dest;
}