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
typedef  enum help_format { ____Placeholder_help_format } help_format ;

/* Variables and functions */
 int HELP_FORMAT_NONE ; 
 int /*<<< orphan*/  add_man_viewer (char const*) ; 
 int add_man_viewer_info (char const*,char const*) ; 
 int config_error_nonbool (char const*) ; 
 int parse_help_format (char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 scalar_t__ strstarts (char const*,char*) ; 

__attribute__((used)) static int perf_help_config(const char *var, const char *value, void *cb)
{
	enum help_format *help_formatp = cb;

	if (!strcmp(var, "help.format")) {
		if (!value)
			return config_error_nonbool(var);
		*help_formatp = parse_help_format(value);
		if (*help_formatp == HELP_FORMAT_NONE)
			return -1;
		return 0;
	}
	if (!strcmp(var, "man.viewer")) {
		if (!value)
			return config_error_nonbool(var);
		add_man_viewer(value);
		return 0;
	}
	if (strstarts(var, "man."))
		return add_man_viewer_info(var, value);

	return 0;
}