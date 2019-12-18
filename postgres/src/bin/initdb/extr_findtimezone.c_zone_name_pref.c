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
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
zone_name_pref(const char *zonename)
{
	/*
	 * Prefer UTC over alternatives such as UCT.  Also prefer Etc/UTC over
	 * Etc/UCT; but UTC is preferred to Etc/UTC.
	 */
	if (strcmp(zonename, "UTC") == 0)
		return 50;
	if (strcmp(zonename, "Etc/UTC") == 0)
		return 40;

	/*
	 * We don't want to pick "localtime" or "posixrules", unless we can find
	 * no other name for the prevailing zone.  Those aren't real zone names.
	 */
	if (strcmp(zonename, "localtime") == 0 ||
		strcmp(zonename, "posixrules") == 0)
		return -50;

	return 0;
}