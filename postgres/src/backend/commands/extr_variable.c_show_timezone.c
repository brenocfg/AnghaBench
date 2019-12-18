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
 char* pg_get_timezone_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  session_timezone ; 

const char *
show_timezone(void)
{
	const char *tzn;

	/* Always show the zone's canonical name */
	tzn = pg_get_timezone_name(session_timezone);

	if (tzn != NULL)
		return tzn;

	return "unknown";
}