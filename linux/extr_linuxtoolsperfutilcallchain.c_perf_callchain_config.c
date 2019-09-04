#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long dump_size; void* print_limit; void* min_percent; } ;

/* Variables and functions */
 TYPE_1__ callchain_param ; 
 int get_stack_size (char const*,unsigned long*) ; 
 int parse_callchain_mode (char const*) ; 
 int parse_callchain_order (char const*) ; 
 int parse_callchain_record_opt (char const*,TYPE_1__*) ; 
 int parse_callchain_sort_key (char const*) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strstarts (char const*,char*) ; 
 void* strtod (char const*,char**) ; 

int perf_callchain_config(const char *var, const char *value)
{
	char *endptr;

	if (!strstarts(var, "call-graph."))
		return 0;
	var += sizeof("call-graph.") - 1;

	if (!strcmp(var, "record-mode"))
		return parse_callchain_record_opt(value, &callchain_param);
	if (!strcmp(var, "dump-size")) {
		unsigned long size = 0;
		int ret;

		ret = get_stack_size(value, &size);
		callchain_param.dump_size = size;

		return ret;
	}
	if (!strcmp(var, "print-type")){
		int ret;
		ret = parse_callchain_mode(value);
		if (ret == -1)
			pr_err("Invalid callchain mode: %s\n", value);
		return ret;
	}
	if (!strcmp(var, "order")){
		int ret;
		ret = parse_callchain_order(value);
		if (ret == -1)
			pr_err("Invalid callchain order: %s\n", value);
		return ret;
	}
	if (!strcmp(var, "sort-key")){
		int ret;
		ret = parse_callchain_sort_key(value);
		if (ret == -1)
			pr_err("Invalid callchain sort key: %s\n", value);
		return ret;
	}
	if (!strcmp(var, "threshold")) {
		callchain_param.min_percent = strtod(value, &endptr);
		if (value == endptr) {
			pr_err("Invalid callchain threshold: %s\n", value);
			return -1;
		}
	}
	if (!strcmp(var, "print-limit")) {
		callchain_param.print_limit = strtod(value, &endptr);
		if (value == endptr) {
			pr_err("Invalid callchain print limit: %s\n", value);
			return -1;
		}
	}

	return 0;
}