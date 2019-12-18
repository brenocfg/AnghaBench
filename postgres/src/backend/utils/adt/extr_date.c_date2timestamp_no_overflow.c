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
typedef  double DateADT ;

/* Variables and functions */
 scalar_t__ DATE_IS_NOBEGIN (double) ; 
 scalar_t__ DATE_IS_NOEND (double) ; 
 double DBL_MAX ; 
 scalar_t__ USECS_PER_DAY ; 

double
date2timestamp_no_overflow(DateADT dateVal)
{
	double		result;

	if (DATE_IS_NOBEGIN(dateVal))
		result = -DBL_MAX;
	else if (DATE_IS_NOEND(dateVal))
		result = DBL_MAX;
	else
	{
		/* date is days since 2000, timestamp is microseconds since same... */
		result = dateVal * (double) USECS_PER_DAY;
	}

	return result;
}