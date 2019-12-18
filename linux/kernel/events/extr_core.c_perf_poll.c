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
struct ring_buffer {int /*<<< orphan*/  poll; } ;
struct perf_event {int /*<<< orphan*/  mmap_mutex; struct ring_buffer* rb; int /*<<< orphan*/  waitq; } ;
struct file {struct perf_event* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int /*<<< orphan*/  __poll_t ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLLHUP ; 
 int /*<<< orphan*/  atomic_xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ is_event_hup (struct perf_event*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t perf_poll(struct file *file, poll_table *wait)
{
	struct perf_event *event = file->private_data;
	struct ring_buffer *rb;
	__poll_t events = EPOLLHUP;

	poll_wait(file, &event->waitq, wait);

	if (is_event_hup(event))
		return events;

	/*
	 * Pin the event->rb by taking event->mmap_mutex; otherwise
	 * perf_event_set_output() can swizzle our rb and make us miss wakeups.
	 */
	mutex_lock(&event->mmap_mutex);
	rb = event->rb;
	if (rb)
		events = atomic_xchg(&rb->poll, 0);
	mutex_unlock(&event->mmap_mutex);
	return events;
}