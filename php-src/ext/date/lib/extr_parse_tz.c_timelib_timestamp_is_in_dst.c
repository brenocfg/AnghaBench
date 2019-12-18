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
struct TYPE_3__ {int isdst; } ;
typedef  TYPE_1__ ttinfo ;
typedef  int /*<<< orphan*/  timelib_tzinfo ;
typedef  int /*<<< orphan*/  timelib_sll ;

/* Variables and functions */
 TYPE_1__* fetch_timezone_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int timelib_timestamp_is_in_dst(timelib_sll ts, timelib_tzinfo *tz)
{
	ttinfo *to;
	timelib_sll dummy;

	if ((to = fetch_timezone_offset(tz, ts, &dummy))) {
		return to->isdst;
	}
	return -1;
}