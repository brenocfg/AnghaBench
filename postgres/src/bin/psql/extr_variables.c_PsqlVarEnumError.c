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
 int /*<<< orphan*/  pg_log_error (char*,char const*,char const*,char const*) ; 

void
PsqlVarEnumError(const char *name, const char *value, const char *suggestions)
{
	pg_log_error("unrecognized value \"%s\" for \"%s\"\n"
				 "Available values are: %s.",
				 value, name, suggestions);
}