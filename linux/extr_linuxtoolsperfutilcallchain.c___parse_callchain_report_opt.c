#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int enabled; scalar_t__ record_mode; unsigned long dump_size; int /*<<< orphan*/  print_limit; int /*<<< orphan*/  min_percent; int /*<<< orphan*/  mode; } ;
struct TYPE_5__ {int use_callchain; } ;

/* Variables and functions */
 scalar_t__ CALLCHAIN_DWARF ; 
 int /*<<< orphan*/  CHAIN_NONE ; 
 TYPE_2__ callchain_param ; 
 scalar_t__ callchain_register_param (TYPE_2__*) ; 
 scalar_t__ get_stack_size (char*,unsigned long*) ; 
 int /*<<< orphan*/  parse_callchain_mode (char*) ; 
 int /*<<< orphan*/  parse_callchain_order (char*) ; 
 scalar_t__ parse_callchain_record (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  parse_callchain_sort_key (char*) ; 
 int /*<<< orphan*/  parse_callchain_value (char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strtod (char*,char**) ; 
 char* strtok_r (char*,char*,char**) ; 
 int /*<<< orphan*/  strtoul (char*,char**,int /*<<< orphan*/ ) ; 
 TYPE_1__ symbol_conf ; 

__attribute__((used)) static int
__parse_callchain_report_opt(const char *arg, bool allow_record_opt)
{
	char *tok;
	char *endptr, *saveptr = NULL;
	bool minpcnt_set = false;
	bool record_opt_set = false;
	bool try_stack_size = false;

	callchain_param.enabled = true;
	symbol_conf.use_callchain = true;

	if (!arg)
		return 0;

	while ((tok = strtok_r((char *)arg, ",", &saveptr)) != NULL) {
		if (!strncmp(tok, "none", strlen(tok))) {
			callchain_param.mode = CHAIN_NONE;
			callchain_param.enabled = false;
			symbol_conf.use_callchain = false;
			return 0;
		}

		if (!parse_callchain_mode(tok) ||
		    !parse_callchain_order(tok) ||
		    !parse_callchain_sort_key(tok) ||
		    !parse_callchain_value(tok)) {
			/* parsing ok - move on to the next */
			try_stack_size = false;
			goto next;
		} else if (allow_record_opt && !record_opt_set) {
			if (parse_callchain_record(tok, &callchain_param))
				goto try_numbers;

			/* assume that number followed by 'dwarf' is stack size */
			if (callchain_param.record_mode == CALLCHAIN_DWARF)
				try_stack_size = true;

			record_opt_set = true;
			goto next;
		}

try_numbers:
		if (try_stack_size) {
			unsigned long size = 0;

			if (get_stack_size(tok, &size) < 0)
				return -1;
			callchain_param.dump_size = size;
			try_stack_size = false;
		} else if (!minpcnt_set) {
			/* try to get the min percent */
			callchain_param.min_percent = strtod(tok, &endptr);
			if (tok == endptr)
				return -1;
			minpcnt_set = true;
		} else {
			/* try print limit at last */
			callchain_param.print_limit = strtoul(tok, &endptr, 0);
			if (tok == endptr)
				return -1;
		}
next:
		arg = NULL;
	}

	if (callchain_register_param(&callchain_param) < 0) {
		pr_err("Can't register callchain params\n");
		return -1;
	}
	return 0;
}