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
struct synth_event {int /*<<< orphan*/  list; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  find_synth_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_synth_event (struct synth_event*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synth_event_list ; 
 int /*<<< orphan*/  synth_event_mutex ; 

__attribute__((used)) static void add_or_delete_synth_event(struct synth_event *event, int delete)
{
	if (delete)
		free_synth_event(event);
	else {
		mutex_lock(&synth_event_mutex);
		if (!find_synth_event(event->name))
			list_add(&event->list, &synth_event_list);
		else
			free_synth_event(event);
		mutex_unlock(&synth_event_mutex);
	}
}