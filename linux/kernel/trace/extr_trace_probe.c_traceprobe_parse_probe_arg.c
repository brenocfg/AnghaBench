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
struct trace_probe {int /*<<< orphan*/  size; struct probe_arg* args; int /*<<< orphan*/  nr_args; } ;
struct probe_arg {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARG_NAME_TOO_LONG ; 
 int /*<<< orphan*/  BAD_ARG_NAME ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_ARG_NAME_LEN ; 
 int /*<<< orphan*/  NO_ARG_NAME ; 
 int /*<<< orphan*/  USED_ARG_NAME ; 
 int /*<<< orphan*/  is_good_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kasprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kmemdup_nul (char*,int,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  trace_probe_log_err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ traceprobe_conflict_field_name (int /*<<< orphan*/ ,struct probe_arg*,int) ; 
 int traceprobe_parse_probe_arg_body (char*,int /*<<< orphan*/ *,struct probe_arg*,unsigned int,int) ; 

int traceprobe_parse_probe_arg(struct trace_probe *tp, int i, char *arg,
				unsigned int flags)
{
	struct probe_arg *parg = &tp->args[i];
	char *body;

	/* Increment count for freeing args in error case */
	tp->nr_args++;

	body = strchr(arg, '=');
	if (body) {
		if (body - arg > MAX_ARG_NAME_LEN) {
			trace_probe_log_err(0, ARG_NAME_TOO_LONG);
			return -EINVAL;
		} else if (body == arg) {
			trace_probe_log_err(0, NO_ARG_NAME);
			return -EINVAL;
		}
		parg->name = kmemdup_nul(arg, body - arg, GFP_KERNEL);
		body++;
	} else {
		/* If argument name is omitted, set "argN" */
		parg->name = kasprintf(GFP_KERNEL, "arg%d", i + 1);
		body = arg;
	}
	if (!parg->name)
		return -ENOMEM;

	if (!is_good_name(parg->name)) {
		trace_probe_log_err(0, BAD_ARG_NAME);
		return -EINVAL;
	}
	if (traceprobe_conflict_field_name(parg->name, tp->args, i)) {
		trace_probe_log_err(0, USED_ARG_NAME);
		return -EINVAL;
	}
	/* Parse fetch argument */
	return traceprobe_parse_probe_arg_body(body, &tp->size, parg, flags,
					       body - arg);
}