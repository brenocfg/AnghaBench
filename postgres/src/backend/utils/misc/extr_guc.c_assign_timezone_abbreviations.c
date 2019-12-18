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
typedef  int /*<<< orphan*/  TimeZoneAbbrevTable ;

/* Variables and functions */
 int /*<<< orphan*/  InstallTimeZoneAbbrevs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
assign_timezone_abbreviations(const char *newval, void *extra)
{
	/* Do nothing for the boot_val default of NULL */
	if (!extra)
		return;

	InstallTimeZoneAbbrevs((TimeZoneAbbrevTable *) extra);
}