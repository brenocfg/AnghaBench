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
struct perf_probe_event {int nargs; struct perf_probe_arg_field* args; int /*<<< orphan*/  point; struct perf_probe_arg_field* target; struct perf_probe_arg_field* group; struct perf_probe_arg_field* event; } ;
struct perf_probe_arg_field {struct perf_probe_arg_field* name; struct perf_probe_arg_field* next; struct perf_probe_arg_field* field; struct perf_probe_arg_field* type; struct perf_probe_arg_field* var; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_perf_probe_point (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct perf_probe_arg_field*) ; 
 int /*<<< orphan*/  memset (struct perf_probe_event*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfree (struct perf_probe_arg_field**) ; 

void clear_perf_probe_event(struct perf_probe_event *pev)
{
	struct perf_probe_arg_field *field, *next;
	int i;

	free(pev->event);
	free(pev->group);
	free(pev->target);
	clear_perf_probe_point(&pev->point);

	for (i = 0; i < pev->nargs; i++) {
		free(pev->args[i].name);
		free(pev->args[i].var);
		free(pev->args[i].type);
		field = pev->args[i].field;
		while (field) {
			next = field->next;
			zfree(&field->name);
			free(field);
			field = next;
		}
	}
	free(pev->args);
	memset(pev, 0, sizeof(*pev));
}