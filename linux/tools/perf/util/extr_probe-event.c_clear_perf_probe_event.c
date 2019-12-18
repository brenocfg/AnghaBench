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
struct perf_probe_event {int nargs; TYPE_1__* args; int /*<<< orphan*/  point; TYPE_1__* target; TYPE_1__* group; TYPE_1__* event; } ;
struct perf_probe_arg_field {TYPE_1__* name; struct perf_probe_arg_field* next; } ;
struct TYPE_2__ {struct perf_probe_arg_field* field; struct TYPE_2__* type; struct TYPE_2__* var; struct TYPE_2__* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_perf_probe_point (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct perf_probe_arg_field*) ; 
 int /*<<< orphan*/  zfree (TYPE_1__**) ; 

void clear_perf_probe_event(struct perf_probe_event *pev)
{
	struct perf_probe_arg_field *field, *next;
	int i;

	zfree(&pev->event);
	zfree(&pev->group);
	zfree(&pev->target);
	clear_perf_probe_point(&pev->point);

	for (i = 0; i < pev->nargs; i++) {
		zfree(&pev->args[i].name);
		zfree(&pev->args[i].var);
		zfree(&pev->args[i].type);
		field = pev->args[i].field;
		while (field) {
			next = field->next;
			zfree(&field->name);
			free(field);
			field = next;
		}
	}
	pev->nargs = 0;
	zfree(&pev->args);
}