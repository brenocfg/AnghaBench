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
 scalar_t__ errno ; 
 scalar_t__ json_output ; 
 int /*<<< orphan*/  json_wtr ; 
 int /*<<< orphan*/  jsonw_int_field (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  jsonw_null_field (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  jsonw_string_field (int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 
 int strtol (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_kernel_option(const char *name, const char *value)
{
	char *endptr;
	int res;

	/* No support for C-style ouptut */

	if (json_output) {
		if (!value) {
			jsonw_null_field(json_wtr, name);
			return;
		}
		errno = 0;
		res = strtol(value, &endptr, 0);
		if (!errno && *endptr == '\n')
			jsonw_int_field(json_wtr, name, res);
		else
			jsonw_string_field(json_wtr, name, value);
	} else {
		if (value)
			printf("%s is set to %s\n", name, value);
		else
			printf("%s is not set\n", name);
	}
}