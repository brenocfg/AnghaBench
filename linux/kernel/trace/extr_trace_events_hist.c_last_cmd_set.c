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
struct trace_event_file {struct trace_event_call* event_call; } ;
struct trace_event_call {TYPE_1__* class; } ;
struct TYPE_2__ {char* system; } ;

/* Variables and functions */
 scalar_t__ MAX_FILTER_STR_VAL ; 
 int /*<<< orphan*/  last_cmd ; 
 int /*<<< orphan*/  last_cmd_loc ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,scalar_t__,char*,char const*,char const*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 char* trace_event_name (struct trace_event_call*) ; 

__attribute__((used)) static void last_cmd_set(struct trace_event_file *file, char *str)
{
	const char *system = NULL, *name = NULL;
	struct trace_event_call *call;

	if (!str)
		return;

	strncpy(last_cmd, str, MAX_FILTER_STR_VAL - 1);

	if (file) {
		call = file->event_call;

		system = call->class->system;
		if (system) {
			name = trace_event_name(call);
			if (!name)
				system = NULL;
		}
	}

	if (system)
		snprintf(last_cmd_loc, MAX_FILTER_STR_VAL, "hist:%s:%s", system, name);
}