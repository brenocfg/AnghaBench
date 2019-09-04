#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int first_last_day_of; scalar_t__ y; scalar_t__ m; scalar_t__ d; scalar_t__ h; scalar_t__ i; scalar_t__ s; scalar_t__ us; scalar_t__ have_weekday_relative; } ;
struct TYPE_7__ {int d; int /*<<< orphan*/  m; TYPE_1__ relative; int /*<<< orphan*/  y; int /*<<< orphan*/  h; int /*<<< orphan*/  i; int /*<<< orphan*/  s; int /*<<< orphan*/  us; scalar_t__ have_relative; } ;
typedef  TYPE_2__ timelib_time ;

/* Variables and functions */
#define  TIMELIB_SPECIAL_FIRST_DAY_OF_MONTH 129 
#define  TIMELIB_SPECIAL_LAST_DAY_OF_MONTH 128 
 int /*<<< orphan*/  do_adjust_for_weekday (TYPE_2__*) ; 
 int /*<<< orphan*/  timelib_do_normalize (TYPE_2__*) ; 

__attribute__((used)) static void do_adjust_relative(timelib_time* time)
{
	if (time->relative.have_weekday_relative) {
		do_adjust_for_weekday(time);
	}
	timelib_do_normalize(time);

	if (time->have_relative) {
		time->us += time->relative.us;

		time->s += time->relative.s;
		time->i += time->relative.i;
		time->h += time->relative.h;

		time->d += time->relative.d;
		time->m += time->relative.m;
		time->y += time->relative.y;
	}

	switch (time->relative.first_last_day_of) {
		case TIMELIB_SPECIAL_FIRST_DAY_OF_MONTH: /* first */
			time->d = 1;
			break;
		case TIMELIB_SPECIAL_LAST_DAY_OF_MONTH: /* last */
			time->d = 0;
			time->m++;
			break;
	}

	timelib_do_normalize(time);
}