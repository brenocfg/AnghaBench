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
struct perf_ftrace {char const* tracer; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strstarts (char const*,char*) ; 

__attribute__((used)) static int perf_ftrace_config(const char *var, const char *value, void *cb)
{
	struct perf_ftrace *ftrace = cb;

	if (!strstarts(var, "ftrace."))
		return 0;

	if (strcmp(var, "ftrace.tracer"))
		return -1;

	if (!strcmp(value, "function_graph") ||
	    !strcmp(value, "function")) {
		ftrace->tracer = value;
		return 0;
	}

	pr_err("Please select \"function_graph\" (default) or \"function\"\n");
	return -1;
}