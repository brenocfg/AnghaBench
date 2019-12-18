#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct state {int typecnt; TYPE_1__* ttis; } ;
struct TYPE_5__ {struct state state; } ;
typedef  TYPE_2__ pg_tz ;
struct TYPE_4__ {long tt_utoff; } ;

/* Variables and functions */

bool
pg_get_timezone_offset(const pg_tz *tz, long int *gmtoff)
{
	/*
	 * The zone could have more than one ttinfo, if it's historically used
	 * more than one abbreviation.  We return true as long as they all have
	 * the same gmtoff.
	 */
	const struct state *sp;
	int			i;

	sp = &tz->state;
	for (i = 1; i < sp->typecnt; i++)
	{
		if (sp->ttis[i].tt_utoff != sp->ttis[0].tt_utoff)
			return false;
	}
	*gmtoff = sp->ttis[0].tt_utoff;
	return true;
}