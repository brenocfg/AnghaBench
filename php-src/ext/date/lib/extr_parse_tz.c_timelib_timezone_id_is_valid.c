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

/* Variables and functions */
 int seek_to_tz_position (unsigned char const**,char*,int /*<<< orphan*/  const*) ; 

int timelib_timezone_id_is_valid(char *timezone, const timelib_tzdb *tzdb)
{
	const unsigned char *tzf;
	return (seek_to_tz_position(&tzf, timezone, tzdb));
}