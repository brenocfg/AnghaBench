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
struct trace_subsystem_dir {int dummy; } ;
struct trace_array {int dummy; } ;
struct filter_parse_error {int dummy; } ;
struct event_filter {int /*<<< orphan*/ * filter_string; } ;

/* Variables and functions */
 int /*<<< orphan*/  append_filter_err (struct trace_array*,struct filter_parse_error*,struct event_filter*) ; 
 int /*<<< orphan*/  create_filter_finish (struct filter_parse_error*) ; 
 int create_filter_start (char*,int,struct filter_parse_error**,struct event_filter**) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int process_system_preds (struct trace_subsystem_dir*,struct trace_array*,struct filter_parse_error*,char*) ; 

__attribute__((used)) static int create_system_filter(struct trace_subsystem_dir *dir,
				struct trace_array *tr,
				char *filter_str, struct event_filter **filterp)
{
	struct filter_parse_error *pe = NULL;
	int err;

	err = create_filter_start(filter_str, true, &pe, filterp);
	if (!err) {
		err = process_system_preds(dir, tr, pe, filter_str);
		if (!err) {
			/* System filters just show a default message */
			kfree((*filterp)->filter_string);
			(*filterp)->filter_string = NULL;
		} else {
			append_filter_err(tr, pe, *filterp);
		}
	}
	create_filter_finish(pe);

	return err;
}