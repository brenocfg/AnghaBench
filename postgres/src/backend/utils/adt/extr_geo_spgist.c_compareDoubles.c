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
typedef  scalar_t__ float8 ;

/* Variables and functions */

__attribute__((used)) static int
compareDoubles(const void *a, const void *b)
{
	float8		x = *(float8 *) a;
	float8		y = *(float8 *) b;

	if (x == y)
		return 0;
	return (x > y) ? 1 : -1;
}