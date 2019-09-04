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
 scalar_t__ strstr (char const*,char*) ; 

__attribute__((used)) static bool valid_only_metric(const char *unit)
{
	if (!unit)
		return false;
	if (strstr(unit, "/sec") ||
	    strstr(unit, "hz") ||
	    strstr(unit, "Hz") ||
	    strstr(unit, "CPUs utilized"))
		return false;
	return true;
}