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
typedef  int /*<<< orphan*/  RangeType ;

/* Variables and functions */
 int CLS_CONTAIN_EMPTY ; 
 int CLS_EMPTY ; 
 int CLS_LOWER_INF ; 
 int CLS_UPPER_INF ; 
 char RANGE_CONTAIN_EMPTY ; 
 char RANGE_EMPTY ; 
 char RANGE_LB_INF ; 
 char RANGE_UB_INF ; 
 char range_get_flags (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
get_gist_range_class(RangeType *range)
{
	int			classNumber;
	char		flags;

	flags = range_get_flags(range);
	if (flags & RANGE_EMPTY)
	{
		classNumber = CLS_EMPTY;
	}
	else
	{
		classNumber = 0;
		if (flags & RANGE_LB_INF)
			classNumber |= CLS_LOWER_INF;
		if (flags & RANGE_UB_INF)
			classNumber |= CLS_UPPER_INF;
		if (flags & RANGE_CONTAIN_EMPTY)
			classNumber |= CLS_CONTAIN_EMPTY;
	}
	return classNumber;
}