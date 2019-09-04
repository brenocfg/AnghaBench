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
typedef  int /*<<< orphan*/  timelib_tzdb ;
typedef  int /*<<< orphan*/  timelib_tz_get_wrapper ;
typedef  int /*<<< orphan*/  timelib_time ;
typedef  int /*<<< orphan*/  timelib_error_container ;

/* Variables and functions */
 int /*<<< orphan*/  default_format_config ; 
 int /*<<< orphan*/ * timelib_parse_from_format_with_map (char*,char*,size_t,int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

timelib_time *timelib_parse_from_format(char *format, char *string, size_t len, timelib_error_container **errors, const timelib_tzdb *tzdb, timelib_tz_get_wrapper tz_get_wrapper)
{
	return timelib_parse_from_format_with_map(format, string, len, errors, tzdb, tz_get_wrapper, &default_format_config);
}