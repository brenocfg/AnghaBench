#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* comments; } ;
struct TYPE_6__ {TYPE_1__ location; struct TYPE_6__* leap_times; struct TYPE_6__* timezone_abbr; struct TYPE_6__* type; struct TYPE_6__* trans_idx; struct TYPE_6__* trans; struct TYPE_6__* name; } ;
typedef  TYPE_2__ timelib_tzinfo ;

/* Variables and functions */
 int /*<<< orphan*/  TIMELIB_TIME_FREE (TYPE_2__*) ; 

void timelib_tzinfo_dtor(timelib_tzinfo *tz)
{
	TIMELIB_TIME_FREE(tz->name);
	TIMELIB_TIME_FREE(tz->trans);
	TIMELIB_TIME_FREE(tz->trans_idx);
	TIMELIB_TIME_FREE(tz->type);
	TIMELIB_TIME_FREE(tz->timezone_abbr);
	TIMELIB_TIME_FREE(tz->leap_times);
	TIMELIB_TIME_FREE(tz->location.comments);
	TIMELIB_TIME_FREE(tz);
	tz = NULL;
}