#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int timelib_sll ;
struct TYPE_11__ {int unit; int multiplier; } ;
typedef  TYPE_4__ timelib_relunit ;
struct TYPE_12__ {TYPE_3__* time; } ;
struct TYPE_8__ {int type; int amount; } ;
struct TYPE_9__ {int us; int s; int i; int h; int d; int m; int y; int weekday; int weekday_behavior; TYPE_1__ special; } ;
struct TYPE_10__ {TYPE_2__ relative; } ;
typedef  TYPE_5__ Scanner ;

/* Variables and functions */
#define  TIMELIB_DAY 136 
 int /*<<< orphan*/  TIMELIB_HAVE_SPECIAL_RELATIVE () ; 
 int /*<<< orphan*/  TIMELIB_HAVE_WEEKDAY_RELATIVE () ; 
#define  TIMELIB_HOUR 135 
#define  TIMELIB_MICROSEC 134 
#define  TIMELIB_MINUTE 133 
#define  TIMELIB_MONTH 132 
#define  TIMELIB_SECOND 131 
#define  TIMELIB_SPECIAL 130 
 int /*<<< orphan*/  TIMELIB_UNHAVE_TIME () ; 
#define  TIMELIB_WEEKDAY 129 
#define  TIMELIB_YEAR 128 
 TYPE_4__* timelib_lookup_relunit (char**) ; 

__attribute__((used)) static void timelib_set_relative(char **ptr, timelib_sll amount, int behavior, Scanner *s)
{
	const timelib_relunit* relunit;

	if (!(relunit = timelib_lookup_relunit(ptr))) {
		return;
	}

	switch (relunit->unit) {
		case TIMELIB_MICROSEC: s->time->relative.us += amount * relunit->multiplier; break;
		case TIMELIB_SECOND:   s->time->relative.s += amount * relunit->multiplier; break;
		case TIMELIB_MINUTE:   s->time->relative.i += amount * relunit->multiplier; break;
		case TIMELIB_HOUR:     s->time->relative.h += amount * relunit->multiplier; break;
		case TIMELIB_DAY:      s->time->relative.d += amount * relunit->multiplier; break;
		case TIMELIB_MONTH:    s->time->relative.m += amount * relunit->multiplier; break;
		case TIMELIB_YEAR:     s->time->relative.y += amount * relunit->multiplier; break;

		case TIMELIB_WEEKDAY:
			TIMELIB_HAVE_WEEKDAY_RELATIVE();
			TIMELIB_UNHAVE_TIME();
			s->time->relative.d += (amount > 0 ? amount - 1 : amount) * 7;
			s->time->relative.weekday = relunit->multiplier;
			s->time->relative.weekday_behavior = behavior;
			break;

		case TIMELIB_SPECIAL:
			TIMELIB_HAVE_SPECIAL_RELATIVE();
			TIMELIB_UNHAVE_TIME();
			s->time->relative.special.type = relunit->multiplier;
			s->time->relative.special.amount = amount;
	}
}