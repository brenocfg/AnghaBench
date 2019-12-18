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
struct trace_event_call {int dummy; } ;
struct trace_array {int dummy; } ;
struct filter_parse_error {int dummy; } ;
struct event_filter {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (struct event_filter*) ; 
 int /*<<< orphan*/  append_filter_err (struct trace_array*,struct filter_parse_error*,struct event_filter*) ; 
 int /*<<< orphan*/  create_filter_finish (struct filter_parse_error*) ; 
 int create_filter_start (char*,int,struct filter_parse_error**,struct event_filter**) ; 
 int process_preds (struct trace_event_call*,char*,struct event_filter*,struct filter_parse_error*) ; 

__attribute__((used)) static int create_filter(struct trace_array *tr,
			 struct trace_event_call *call,
			 char *filter_string, bool set_str,
			 struct event_filter **filterp)
{
	struct filter_parse_error *pe = NULL;
	int err;

	/* filterp must point to NULL */
	if (WARN_ON(*filterp))
		*filterp = NULL;

	err = create_filter_start(filter_string, set_str, &pe, filterp);
	if (err)
		return err;

	err = process_preds(call, filter_string, *filterp, pe);
	if (err && set_str)
		append_filter_err(tr, pe, *filterp);
	create_filter_finish(pe);

	return err;
}