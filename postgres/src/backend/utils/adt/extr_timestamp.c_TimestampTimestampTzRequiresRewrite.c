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

/* Variables and functions */
 scalar_t__ pg_get_timezone_offset (int /*<<< orphan*/ ,long*) ; 
 int /*<<< orphan*/  session_timezone ; 

bool
TimestampTimestampTzRequiresRewrite(void)
{
	long		offset;

	if (pg_get_timezone_offset(session_timezone, &offset) && offset == 0)
		return false;
	return true;
}