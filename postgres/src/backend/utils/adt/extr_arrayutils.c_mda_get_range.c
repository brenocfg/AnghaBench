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

void
mda_get_range(int n, int *span, const int *st, const int *endp)
{
	int			i;

	for (i = 0; i < n; i++)
		span[i] = endp[i] - st[i] + 1;
}