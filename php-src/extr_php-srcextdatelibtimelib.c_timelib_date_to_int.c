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
struct TYPE_3__ {scalar_t__ sse; } ;
typedef  TYPE_1__ timelib_time ;
typedef  scalar_t__ timelib_sll ;
typedef  int /*<<< orphan*/  timelib_long ;

/* Variables and functions */
 scalar_t__ TIMELIB_LONG_MAX ; 
 scalar_t__ TIMELIB_LONG_MIN ; 

timelib_long timelib_date_to_int(timelib_time *d, int *error)
{
	timelib_sll ts;

	ts = d->sse;

	if (ts < TIMELIB_LONG_MIN || ts > TIMELIB_LONG_MAX) {
		if (error) {
			*error = 1;
		}
		return 0;
	}
	if (error) {
		*error = 0;
	}
	return (timelib_long) d->sse;
}