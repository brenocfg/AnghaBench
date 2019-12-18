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

/* Variables and functions */
 scalar_t__ ERANGE ; 
 scalar_t__ PG_INT64_MAX ; 
 scalar_t__ PG_INT64_MIN ; 
 scalar_t__ errno ; 
 scalar_t__ hi_time ; 
 scalar_t__ lo_time ; 
 scalar_t__ max_time ; 
 scalar_t__ min_time ; 
 scalar_t__ strtoimax (char*,char**,int) ; 

__attribute__((used)) static bool
timerange_option(char *timerange)
{
	int64		lo = min_time,
				hi = max_time;
	char	   *lo_end = timerange,
			   *hi_end;

	if (*timerange == '@')
	{
		errno = 0;
		lo = strtoimax(timerange + 1, &lo_end, 10);
		if (lo_end == timerange + 1 || (lo == PG_INT64_MAX && errno == ERANGE))
			return false;
	}
	hi_end = lo_end;
	if (lo_end[0] == '/' && lo_end[1] == '@')
	{
		errno = 0;
		hi = strtoimax(lo_end + 2, &hi_end, 10);
		if (hi_end == lo_end + 2 || hi == PG_INT64_MIN)
			return false;
		hi -= !(hi == PG_INT64_MAX && errno == ERANGE);
	}
	if (*hi_end || hi < lo || max_time < lo || hi < min_time)
		return false;
	lo_time = lo < min_time ? min_time : lo;
	hi_time = max_time < hi ? max_time : hi;
	return true;
}