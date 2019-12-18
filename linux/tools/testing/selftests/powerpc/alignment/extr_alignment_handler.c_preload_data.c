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

void preload_data(void *dst, int offset, int width)
{
	char *c = dst;
	int i;

	c += offset;

	for (i = 0 ; i < width ; i++)
		c[i] = i;
}