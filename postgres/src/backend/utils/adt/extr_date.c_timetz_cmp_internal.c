#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ time; int zone; } ;
typedef  TYPE_1__ TimeTzADT ;
typedef  scalar_t__ TimeOffset ;

/* Variables and functions */
 int USECS_PER_SEC ; 

__attribute__((used)) static int
timetz_cmp_internal(TimeTzADT *time1, TimeTzADT *time2)
{
	TimeOffset	t1,
				t2;

	/* Primary sort is by true (GMT-equivalent) time */
	t1 = time1->time + (time1->zone * USECS_PER_SEC);
	t2 = time2->time + (time2->zone * USECS_PER_SEC);

	if (t1 > t2)
		return 1;
	if (t1 < t2)
		return -1;

	/*
	 * If same GMT time, sort by timezone; we only want to say that two
	 * timetz's are equal if both the time and zone parts are equal.
	 */
	if (time1->zone > time2->zone)
		return 1;
	if (time1->zone < time2->zone)
		return -1;

	return 0;
}