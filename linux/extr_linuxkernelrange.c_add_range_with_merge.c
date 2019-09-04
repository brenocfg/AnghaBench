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
typedef  int /*<<< orphan*/  range ;

/* Variables and functions */
 int add_range (struct range*,int,int,scalar_t__,scalar_t__) ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memmove (struct range*,struct range*,int) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 

int add_range_with_merge(struct range *range, int az, int nr_range,
		     u64 start, u64 end)
{
	int i;

	if (start >= end)
		return nr_range;

	/* get new start/end: */
	for (i = 0; i < nr_range; i++) {
		u64 common_start, common_end;

		if (!range[i].end)
			continue;

		common_start = max(range[i].start, start);
		common_end = min(range[i].end, end);
		if (common_start > common_end)
			continue;

		/* new start/end, will add it back at last */
		start = min(range[i].start, start);
		end = max(range[i].end, end);

		memmove(&range[i], &range[i + 1],
			(nr_range - (i + 1)) * sizeof(range[i]));
		range[nr_range - 1].start = 0;
		range[nr_range - 1].end   = 0;
		nr_range--;
		i--;
	}

	/* Need to add it: */
	return add_range(range, az, nr_range, start, end);
}