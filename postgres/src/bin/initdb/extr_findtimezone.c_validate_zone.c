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
typedef  int /*<<< orphan*/  pg_tz ;

/* Variables and functions */
 int /*<<< orphan*/ * pg_load_tz (char const*) ; 
 int /*<<< orphan*/  pg_tz_acceptable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
validate_zone(const char *tzname)
{
	pg_tz	   *tz;

	if (!tzname || !tzname[0])
		return false;

	tz = pg_load_tz(tzname);
	if (!tz)
		return false;

	if (!pg_tz_acceptable(tz))
		return false;

	return true;
}