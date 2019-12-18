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
struct event_struct {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_EVENT_FIELD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FOR_ALL_EVENT_STRUCT_FIELDS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FREE_EVENT_FIELD ; 
 int /*<<< orphan*/  arch_std_events ; 
 int /*<<< orphan*/  free (struct event_struct*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct event_struct* malloc (int) ; 
 int /*<<< orphan*/  memset (struct event_struct*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int save_arch_std_events(void *data, char *name, char *event,
				char *desc, char *long_desc, char *pmu,
				char *unit, char *perpkg, char *metric_expr,
				char *metric_name, char *metric_group)
{
	struct event_struct *es;

	es = malloc(sizeof(*es));
	if (!es)
		return -ENOMEM;
	memset(es, 0, sizeof(*es));
	FOR_ALL_EVENT_STRUCT_FIELDS(ADD_EVENT_FIELD);
	list_add_tail(&es->list, &arch_std_events);
	return 0;
out_free:
	FOR_ALL_EVENT_STRUCT_FIELDS(FREE_EVENT_FIELD);
	free(es);
	return -ENOMEM;
}