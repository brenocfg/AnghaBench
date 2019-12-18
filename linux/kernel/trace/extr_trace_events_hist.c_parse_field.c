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
struct trace_event_file {int /*<<< orphan*/  event_call; struct trace_array* tr; } ;
struct trace_array {int dummy; } ;
struct hist_trigger_data {int enable_timestamps; TYPE_1__* attrs; } ;
struct ftrace_event_field {int /*<<< orphan*/  size; } ;
struct TYPE_2__ {int ts_in_usecs; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct ftrace_event_field* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HIST_ERR_BAD_FIELD_MODIFIER ; 
 int /*<<< orphan*/  HIST_ERR_FIELD_NOT_FOUND ; 
 unsigned long HIST_FIELD_FL_CPU ; 
 unsigned long HIST_FIELD_FL_EXECNAME ; 
 unsigned long HIST_FIELD_FL_HEX ; 
 unsigned long HIST_FIELD_FL_LOG2 ; 
 unsigned long HIST_FIELD_FL_SYM ; 
 unsigned long HIST_FIELD_FL_SYM_OFFSET ; 
 unsigned long HIST_FIELD_FL_SYSCALL ; 
 unsigned long HIST_FIELD_FL_TIMESTAMP ; 
 unsigned long HIST_FIELD_FL_TIMESTAMP_USECS ; 
 int /*<<< orphan*/  errpos (char*) ; 
 int /*<<< orphan*/  hist_err (struct trace_array*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strsep (char**,char*) ; 
 struct ftrace_event_field* trace_find_event_field (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct ftrace_event_field *
parse_field(struct hist_trigger_data *hist_data, struct trace_event_file *file,
	    char *field_str, unsigned long *flags)
{
	struct ftrace_event_field *field = NULL;
	char *field_name, *modifier, *str;
	struct trace_array *tr = file->tr;

	modifier = str = kstrdup(field_str, GFP_KERNEL);
	if (!modifier)
		return ERR_PTR(-ENOMEM);

	field_name = strsep(&modifier, ".");
	if (modifier) {
		if (strcmp(modifier, "hex") == 0)
			*flags |= HIST_FIELD_FL_HEX;
		else if (strcmp(modifier, "sym") == 0)
			*flags |= HIST_FIELD_FL_SYM;
		else if (strcmp(modifier, "sym-offset") == 0)
			*flags |= HIST_FIELD_FL_SYM_OFFSET;
		else if ((strcmp(modifier, "execname") == 0) &&
			 (strcmp(field_name, "common_pid") == 0))
			*flags |= HIST_FIELD_FL_EXECNAME;
		else if (strcmp(modifier, "syscall") == 0)
			*flags |= HIST_FIELD_FL_SYSCALL;
		else if (strcmp(modifier, "log2") == 0)
			*flags |= HIST_FIELD_FL_LOG2;
		else if (strcmp(modifier, "usecs") == 0)
			*flags |= HIST_FIELD_FL_TIMESTAMP_USECS;
		else {
			hist_err(tr, HIST_ERR_BAD_FIELD_MODIFIER, errpos(modifier));
			field = ERR_PTR(-EINVAL);
			goto out;
		}
	}

	if (strcmp(field_name, "common_timestamp") == 0) {
		*flags |= HIST_FIELD_FL_TIMESTAMP;
		hist_data->enable_timestamps = true;
		if (*flags & HIST_FIELD_FL_TIMESTAMP_USECS)
			hist_data->attrs->ts_in_usecs = true;
	} else if (strcmp(field_name, "cpu") == 0)
		*flags |= HIST_FIELD_FL_CPU;
	else {
		field = trace_find_event_field(file->event_call, field_name);
		if (!field || !field->size) {
			hist_err(tr, HIST_ERR_FIELD_NOT_FOUND, errpos(field_name));
			field = ERR_PTR(-EINVAL);
			goto out;
		}
	}
 out:
	kfree(str);

	return field;
}