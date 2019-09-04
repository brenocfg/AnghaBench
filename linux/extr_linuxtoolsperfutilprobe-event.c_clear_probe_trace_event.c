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
struct TYPE_2__ {struct probe_trace_arg_ref* module; struct probe_trace_arg_ref* realname; struct probe_trace_arg_ref* symbol; } ;
struct probe_trace_event {int nargs; struct probe_trace_arg_ref* args; TYPE_1__ point; struct probe_trace_arg_ref* group; struct probe_trace_arg_ref* event; } ;
struct probe_trace_arg_ref {struct probe_trace_arg_ref* next; struct probe_trace_arg_ref* ref; struct probe_trace_arg_ref* type; struct probe_trace_arg_ref* value; struct probe_trace_arg_ref* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct probe_trace_arg_ref*) ; 
 int /*<<< orphan*/  memset (struct probe_trace_event*,int /*<<< orphan*/ ,int) ; 

void clear_probe_trace_event(struct probe_trace_event *tev)
{
	struct probe_trace_arg_ref *ref, *next;
	int i;

	free(tev->event);
	free(tev->group);
	free(tev->point.symbol);
	free(tev->point.realname);
	free(tev->point.module);
	for (i = 0; i < tev->nargs; i++) {
		free(tev->args[i].name);
		free(tev->args[i].value);
		free(tev->args[i].type);
		ref = tev->args[i].ref;
		while (ref) {
			next = ref->next;
			free(ref);
			ref = next;
		}
	}
	free(tev->args);
	memset(tev, 0, sizeof(*tev));
}