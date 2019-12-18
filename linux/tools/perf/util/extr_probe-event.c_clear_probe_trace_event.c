#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {TYPE_2__* module; TYPE_2__* realname; TYPE_2__* symbol; } ;
struct probe_trace_event {int nargs; TYPE_2__* args; TYPE_1__ point; TYPE_2__* group; TYPE_2__* event; } ;
struct probe_trace_arg_ref {struct probe_trace_arg_ref* next; } ;
struct TYPE_4__ {struct probe_trace_arg_ref* ref; struct TYPE_4__* type; struct TYPE_4__* value; struct TYPE_4__* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct probe_trace_arg_ref*) ; 
 int /*<<< orphan*/  zfree (TYPE_2__**) ; 

void clear_probe_trace_event(struct probe_trace_event *tev)
{
	struct probe_trace_arg_ref *ref, *next;
	int i;

	zfree(&tev->event);
	zfree(&tev->group);
	zfree(&tev->point.symbol);
	zfree(&tev->point.realname);
	zfree(&tev->point.module);
	for (i = 0; i < tev->nargs; i++) {
		zfree(&tev->args[i].name);
		zfree(&tev->args[i].value);
		zfree(&tev->args[i].type);
		ref = tev->args[i].ref;
		while (ref) {
			next = ref->next;
			free(ref);
			ref = next;
		}
	}
	zfree(&tev->args);
	tev->nargs = 0;
}