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
 int MAX_FILTER_STR_VAL ; 
 int /*<<< orphan*/  hist_err (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,...) ; 
 int /*<<< orphan*/  strscpy (char*,char*,int) ; 

__attribute__((used)) static void hist_err_event(char *str, char *system, char *event, char *var)
{
	char err[MAX_FILTER_STR_VAL];

	if (system && var)
		snprintf(err, MAX_FILTER_STR_VAL, "%s.%s.%s", system, event, var);
	else if (system)
		snprintf(err, MAX_FILTER_STR_VAL, "%s.%s", system, event);
	else
		strscpy(err, var, MAX_FILTER_STR_VAL);

	hist_err(str, err);
}