#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int d; int y; int m; } ;
typedef  TYPE_1__ timelib_time ;
typedef  int timelib_sll ;

/* Variables and functions */
 int EPOCH_DAY ; 

__attribute__((used)) static void magic_date_calc(timelib_time *time)
{
	timelib_sll y, ddd, mi, mm, dd, g;

	/* The algorithm doesn't work before the year 1 */
	if (time->d < -719498) {
		return;
	}

	g = time->d + EPOCH_DAY - 1;

	y = (10000 * g + 14780) / 3652425;
	ddd = g - ((365*y) + (y/4) - (y/100) + (y/400));
	if (ddd < 0) {
		y--;
		ddd = g - ((365*y) + (y/4) - (y/100) + (y/400));
	}
	mi = (100 * ddd + 52) / 3060;
	mm = ((mi + 2) % 12) + 1;
	y = y + (mi + 2) / 12;
	dd = ddd - ((mi * 306 + 5) / 10) + 1;
	time->y = y;
	time->m = mm;
	time->d = dd;
}