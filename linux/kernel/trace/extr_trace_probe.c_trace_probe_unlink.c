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
struct trace_probe {int /*<<< orphan*/ * event; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_probe_event_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_probe_probe_list (struct trace_probe*) ; 

void trace_probe_unlink(struct trace_probe *tp)
{
	list_del_init(&tp->list);
	if (list_empty(trace_probe_probe_list(tp)))
		trace_probe_event_free(tp->event);
	tp->event = NULL;
}