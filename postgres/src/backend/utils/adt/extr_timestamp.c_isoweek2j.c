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
 int date2j (int,int,int) ; 
 int j2day (int) ; 

int
isoweek2j(int year, int week)
{
	int			day0,
				day4;

	/* fourth day of current year */
	day4 = date2j(year, 1, 4);

	/* day0 == offset to first day of week (Monday) */
	day0 = j2day(day4 - 1);

	return ((week - 1) * 7) + (day4 - day0);
}