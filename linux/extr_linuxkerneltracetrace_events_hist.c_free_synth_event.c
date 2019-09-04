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
struct TYPE_2__ {struct synth_event* system; } ;
struct synth_event {unsigned int n_fields; int /*<<< orphan*/  call; int /*<<< orphan*/  tp; TYPE_1__ class; struct synth_event* name; struct synth_event* fields; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_synth_event_print_fmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_synth_field (struct synth_event) ; 
 int /*<<< orphan*/  free_synth_tracepoint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct synth_event*) ; 

__attribute__((used)) static void free_synth_event(struct synth_event *event)
{
	unsigned int i;

	if (!event)
		return;

	for (i = 0; i < event->n_fields; i++)
		free_synth_field(event->fields[i]);

	kfree(event->fields);
	kfree(event->name);
	kfree(event->class.system);
	free_synth_tracepoint(event->tp);
	free_synth_event_print_fmt(&event->call);
	kfree(event);
}