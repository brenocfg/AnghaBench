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
typedef  int /*<<< orphan*/  timelib_tz_lookup_table ;

/* Variables and functions */
 int /*<<< orphan*/  const* timelib_timezone_lookup ; 

const timelib_tz_lookup_table *timelib_timezone_abbreviations_list(void)
{
	return timelib_timezone_lookup;
}