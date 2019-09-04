#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  timelib_rel_time ;

/* Variables and functions */
 int /*<<< orphan*/  TIMELIB_TIME_FREE (int /*<<< orphan*/ *) ; 

void timelib_rel_time_dtor(timelib_rel_time* t)
{
	TIMELIB_TIME_FREE(t);
}