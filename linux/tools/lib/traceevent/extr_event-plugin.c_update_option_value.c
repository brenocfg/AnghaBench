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
struct tep_plugin_option {char const* value; int set; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  lower_case (char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static int update_option_value(struct tep_plugin_option *op, const char *val)
{
	char *op_val;

	if (!val) {
		/* toggle, only if option is boolean */
		if (op->value)
			/* Warn? */
			return 0;
		op->set ^= 1;
		return 0;
	}

	/*
	 * If the option has a value then it takes a string
	 * otherwise the option is a boolean.
	 */
	if (op->value) {
		op->value = val;
		return 0;
	}

	/* Option is boolean, must be either "1", "0", "true" or "false" */

	op_val = strdup(val);
	if (!op_val)
		return -1;
	lower_case(op_val);

	if (strcmp(val, "1") == 0 || strcmp(val, "true") == 0)
		op->set = 1;
	else if (strcmp(val, "0") == 0 || strcmp(val, "false") == 0)
		op->set = 0;
	free(op_val);

	return 0;
}