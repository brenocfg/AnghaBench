#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int type; } ;
struct TYPE_7__ {int first_last_day_of; int /*<<< orphan*/  m; TYPE_1__ special; scalar_t__ have_special_relative; } ;
struct TYPE_8__ {int d; int /*<<< orphan*/  m; TYPE_2__ relative; } ;
typedef  TYPE_3__ timelib_time ;

/* Variables and functions */
#define  TIMELIB_SPECIAL_DAY_OF_WEEK_IN_MONTH 131 
#define  TIMELIB_SPECIAL_FIRST_DAY_OF_MONTH 130 
#define  TIMELIB_SPECIAL_LAST_DAY_OF_MONTH 129 
#define  TIMELIB_SPECIAL_LAST_DAY_OF_WEEK_IN_MONTH 128 
 int /*<<< orphan*/  timelib_do_normalize (TYPE_3__*) ; 

__attribute__((used)) static void do_adjust_special_early(timelib_time* time)
{
	if (time->relative.have_special_relative) {
		switch (time->relative.special.type) {
			case TIMELIB_SPECIAL_DAY_OF_WEEK_IN_MONTH:
				time->d = 1;
				time->m += time->relative.m;
				time->relative.m = 0;
				break;
			case TIMELIB_SPECIAL_LAST_DAY_OF_WEEK_IN_MONTH:
				time->d = 1;
				time->m += time->relative.m + 1;
				time->relative.m = 0;
				break;
		}
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