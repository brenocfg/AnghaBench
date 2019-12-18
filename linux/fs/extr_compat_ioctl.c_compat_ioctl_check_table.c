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
 int ARRAY_SIZE (unsigned int*) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 unsigned int* ioctl_pointer ; 

__attribute__((used)) static int compat_ioctl_check_table(unsigned int xcmd)
{
	int i;
	const int max = ARRAY_SIZE(ioctl_pointer) - 1;

	BUILD_BUG_ON(max >= (1 << 16));

	/* guess initial offset into table, assuming a
	   normalized distribution */
	i = ((xcmd >> 16) * max) >> 16;

	/* do linear search up first, until greater or equal */
	while (ioctl_pointer[i] < xcmd && i < max)
		i++;

	/* then do linear search down */
	while (ioctl_pointer[i] > xcmd && i > 0)
		i--;

	return ioctl_pointer[i] == xcmd;
}