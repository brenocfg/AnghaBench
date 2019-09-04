#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int amount; } ;
struct TYPE_6__ {TYPE_1__ special; } ;
struct TYPE_7__ {int d; int /*<<< orphan*/  m; int /*<<< orphan*/  y; TYPE_2__ relative; } ;
typedef  TYPE_3__ timelib_time ;
typedef  int timelib_sll ;

/* Variables and functions */
 int timelib_day_of_week (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void do_adjust_special_weekday(timelib_time* time)
{
	timelib_sll count, dow, rem;

	count = time->relative.special.amount;
	dow = timelib_day_of_week(time->y, time->m, time->d);

	/* Add increments of 5 weekdays as a week, leaving the DOW unchanged. */
	time->d += (count / 5) * 7;

	/* Deal with the remainder. */
	rem = (count % 5);

	if (count > 0) {
		if (rem == 0) {
			/* Head back to Friday if we stop on the weekend. */
			if (dow == 0) {
				time->d -= 2;
			} else if (dow == 6) {
				time->d -= 1;
			}
		} else if (dow == 6) {
			/* We ended up on Saturday, but there's still work to do, so move
			 * to Sunday and continue from there. */
			time->d += 1;
		} else if (dow + rem > 5) {
			/* We're on a weekday, but we're going past Friday, so skip right
			 * over the weekend. */
			time->d += 2;
		}
	} else {
		/* Completely mirror the forward direction. This also covers the 0
		 * case, since if we start on the weekend, we want to move forward as
		 * if we stopped there while going backwards. */
		if (rem == 0) {
			if (dow == 6) {
				time->d += 2;
			} else if (dow == 0) {
				time->d += 1;
			}
		} else if (dow == 0) {
			time->d -= 1;
		} else if (dow + rem < 1) {
			time->d -= 2;
		}
	}

	time->d += rem;
}