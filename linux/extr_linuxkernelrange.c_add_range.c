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
typedef  scalar_t__ u64 ;
struct range {scalar_t__ end; scalar_t__ start; } ;

/* Variables and functions */

int add_range(struct range *range, int az, int nr_range, u64 start, u64 end)
{
	if (start >= end)
		return nr_range;

	/* Out of slots: */
	if (nr_range >= az)
		return nr_range;

	range[nr_range].start = start;
	range[nr_range].end = end;

	nr_range++;

	return nr_range;
}