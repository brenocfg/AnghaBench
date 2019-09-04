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
struct check {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct check**) ; 
 struct check** check_table ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 int /*<<< orphan*/  disable_warning_error (struct check*,int,int) ; 
 int /*<<< orphan*/  enable_warning_error (struct check*,int,int) ; 
 scalar_t__ streq (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

void parse_checks_option(bool warn, bool error, const char *arg)
{
	int i;
	const char *name = arg;
	bool enable = true;

	if ((strncmp(arg, "no-", 3) == 0)
	    || (strncmp(arg, "no_", 3) == 0)) {
		name = arg + 3;
		enable = false;
	}

	for (i = 0; i < ARRAY_SIZE(check_table); i++) {
		struct check *c = check_table[i];

		if (streq(c->name, name)) {
			if (enable)
				enable_warning_error(c, warn, error);
			else
				disable_warning_error(c, warn, error);
			return;
		}
	}

	die("Unrecognized check name \"%s\"\n", name);
}