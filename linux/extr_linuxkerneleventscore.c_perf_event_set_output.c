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
struct ring_buffer {int dummy; } ;
struct perf_event {int cpu; scalar_t__ ctx; scalar_t__ clock; scalar_t__ pmu; int /*<<< orphan*/  mmap_mutex; int /*<<< orphan*/  mmap_count; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ has_aux (struct perf_event*) ; 
 scalar_t__ is_write_backward (struct perf_event*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ring_buffer_attach (struct perf_event*,struct ring_buffer*) ; 
 struct ring_buffer* ring_buffer_get (struct perf_event*) ; 

__attribute__((used)) static int
perf_event_set_output(struct perf_event *event, struct perf_event *output_event)
{
	struct ring_buffer *rb = NULL;
	int ret = -EINVAL;

	if (!output_event)
		goto set;

	/* don't allow circular references */
	if (event == output_event)
		goto out;

	/*
	 * Don't allow cross-cpu buffers
	 */
	if (output_event->cpu != event->cpu)
		goto out;

	/*
	 * If its not a per-cpu rb, it must be the same task.
	 */
	if (output_event->cpu == -1 && output_event->ctx != event->ctx)
		goto out;

	/*
	 * Mixing clocks in the same buffer is trouble you don't need.
	 */
	if (output_event->clock != event->clock)
		goto out;

	/*
	 * Either writing ring buffer from beginning or from end.
	 * Mixing is not allowed.
	 */
	if (is_write_backward(output_event) != is_write_backward(event))
		goto out;

	/*
	 * If both events generate aux data, they must be on the same PMU
	 */
	if (has_aux(event) && has_aux(output_event) &&
	    event->pmu != output_event->pmu)
		goto out;

set:
	mutex_lock(&event->mmap_mutex);
	/* Can't redirect output if we've got an active mmap() */
	if (atomic_read(&event->mmap_count))
		goto unlock;

	if (output_event) {
		/* get the rb we want to redirect to */
		rb = ring_buffer_get(output_event);
		if (!rb)
			goto unlock;
	}

	ring_buffer_attach(event, rb);

	ret = 0;
unlock:
	mutex_unlock(&event->mmap_mutex);

out:
	return ret;
}