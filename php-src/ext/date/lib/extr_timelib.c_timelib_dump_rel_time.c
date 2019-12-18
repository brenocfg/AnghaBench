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
struct TYPE_3__ {int first_last_day_of; scalar_t__ invert; int /*<<< orphan*/  days; int /*<<< orphan*/  s; int /*<<< orphan*/  i; int /*<<< orphan*/  h; int /*<<< orphan*/  d; int /*<<< orphan*/  m; int /*<<< orphan*/  y; } ;
typedef  TYPE_1__ timelib_rel_time ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

void timelib_dump_rel_time(timelib_rel_time *d)
{
	printf("%3lldY %3lldM %3lldD / %3lldH %3lldM %3lldS (days: %lld)%s",
		d->y, d->m, d->d, d->h, d->i, d->s, d->days, d->invert ? " inverted" : "");
	if (d->first_last_day_of != 0) {
		switch (d->first_last_day_of) {
			case 1:
				printf(" / first day of");
				break;
			case 2:
				printf(" / last day of");
				break;
		}
	}
	printf("\n");
}