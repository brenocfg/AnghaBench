#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* no_inherit; } ;
struct trace {int show_zeros; int args_alignment; TYPE_1__ opts; void* show_string_prefix; void* show_arg_names; void* show_duration; void* show_tstamp; int /*<<< orphan*/  evlist; } ;
struct option {int dummy; } ;

/* Variables and functions */
 struct option OPT_CALLBACK (char,char*,int /*<<< orphan*/ *,char*,char*,scalar_t__ (*) (struct option*,char const*,int /*<<< orphan*/ )) ; 
 scalar_t__ parse_events_option (struct option*,char const*,int /*<<< orphan*/ ) ; 
 void* perf_config_bool (char const*,char const*) ; 
 scalar_t__ perf_config_int (int*,char const*,char const*) ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int trace__config(const char *var, const char *value, void *arg)
{
	struct trace *trace = arg;
	int err = 0;

	if (!strcmp(var, "trace.add_events")) {
		struct option o = OPT_CALLBACK('e', "event", &trace->evlist, "event",
					       "event selector. use 'perf list' to list available events",
					       parse_events_option);
		/*
		 * We can't propagate parse_event_option() return, as it is 1
		 * for failure while perf_config() expects -1.
		 */
		if (parse_events_option(&o, value, 0))
			err = -1;
	} else if (!strcmp(var, "trace.show_timestamp")) {
		trace->show_tstamp = perf_config_bool(var, value);
	} else if (!strcmp(var, "trace.show_duration")) {
		trace->show_duration = perf_config_bool(var, value);
	} else if (!strcmp(var, "trace.show_arg_names")) {
		trace->show_arg_names = perf_config_bool(var, value);
		if (!trace->show_arg_names)
			trace->show_zeros = true;
	} else if (!strcmp(var, "trace.show_zeros")) {
		bool new_show_zeros = perf_config_bool(var, value);
		if (!trace->show_arg_names && !new_show_zeros) {
			pr_warning("trace.show_zeros has to be set when trace.show_arg_names=no\n");
			goto out;
		}
		trace->show_zeros = new_show_zeros;
	} else if (!strcmp(var, "trace.show_prefix")) {
		trace->show_string_prefix = perf_config_bool(var, value);
	} else if (!strcmp(var, "trace.no_inherit")) {
		trace->opts.no_inherit = perf_config_bool(var, value);
	} else if (!strcmp(var, "trace.args_alignment")) {
		int args_alignment = 0;
		if (perf_config_int(&args_alignment, var, value) == 0)
			trace->args_alignment = args_alignment;
	}
out:
	return err;
}