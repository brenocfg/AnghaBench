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
struct TYPE_4__ {scalar_t__ us; int s; int i; int h; int d; int m; int y; } ;
typedef  TYPE_1__ timelib_time ;

/* Variables and functions */
 scalar_t__ TIMELIB_UNSET ; 
 int /*<<< orphan*/  do_range_limit (int,int,int,int*,int*) ; 
 scalar_t__ do_range_limit_days (int*,int*,int*) ; 
 int /*<<< orphan*/  magic_date_calc (TYPE_1__*) ; 

void timelib_do_normalize(timelib_time* time)
{
	if (time->us != TIMELIB_UNSET) do_range_limit(0, 1000000, 1000000, &time->us, &time->s);
	if (time->s != TIMELIB_UNSET) do_range_limit(0, 60, 60, &time->s, &time->i);
	if (time->s != TIMELIB_UNSET) do_range_limit(0, 60, 60, &time->i, &time->h);
	if (time->s != TIMELIB_UNSET) do_range_limit(0, 24, 24, &time->h, &time->d);
	do_range_limit(1, 13, 12, &time->m, &time->y);

	/* Short cut if we're doing things against the Epoch */
	if (time->y == 1970 && time->m == 1 && time->d != 1) {
		magic_date_calc(time);
	}

	do {} while (do_range_limit_days(&time->y, &time->m, &time->d));
	do_range_limit(1, 13, 12, &time->m, &time->y);
}