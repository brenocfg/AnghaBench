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
typedef  scalar_t__ int64 ;
typedef  int /*<<< orphan*/  a ;

/* Variables and functions */
 scalar_t__ INT_MAX ; 
 scalar_t__ INT_MIN ; 

int
internal_size(int *a, int len)
{
	int			i;
	int64		size = 0;

	for (i = 0; i < len; i += 2)
	{
		if (!i || a[i] != a[i - 1]) /* do not count repeated range */
			size += (int64) (a[i + 1]) - (int64) (a[i]) + 1;
	}

	if (size > (int64) INT_MAX || size < (int64) INT_MIN)
		return -1;				/* overflow */
	return (int) size;
}