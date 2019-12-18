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
struct trace_probe {int /*<<< orphan*/  list; int /*<<< orphan*/  event; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_probe_event_free (int /*<<< orphan*/ ) ; 
 scalar_t__ trace_probe_has_sibling (struct trace_probe*) ; 
 int /*<<< orphan*/  trace_probe_probe_list (struct trace_probe*) ; 

int trace_probe_append(struct trace_probe *tp, struct trace_probe *to)
{
	if (trace_probe_has_sibling(tp))
		return -EBUSY;

	list_del_init(&tp->list);
	trace_probe_event_free(tp->event);

	tp->event = to->event;
	list_add_tail(&tp->list, trace_probe_probe_list(to));

	return 0;
}