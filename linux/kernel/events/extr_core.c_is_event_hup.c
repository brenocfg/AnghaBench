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
struct perf_event {scalar_t__ state; int /*<<< orphan*/  child_mutex; int /*<<< orphan*/  child_list; } ;

/* Variables and functions */
 scalar_t__ PERF_EVENT_STATE_EXIT ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool is_event_hup(struct perf_event *event)
{
	bool no_children;

	if (event->state > PERF_EVENT_STATE_EXIT)
		return false;

	mutex_lock(&event->child_mutex);
	no_children = list_empty(&event->child_list);
	mutex_unlock(&event->child_mutex);
	return no_children;
}