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
struct ring_buffer {int /*<<< orphan*/  refcount; } ;
struct perf_event {int /*<<< orphan*/  rb; } ;

/* Variables and functions */
 struct ring_buffer* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  refcount_inc_not_zero (int /*<<< orphan*/ *) ; 

struct ring_buffer *ring_buffer_get(struct perf_event *event)
{
	struct ring_buffer *rb;

	rcu_read_lock();
	rb = rcu_dereference(event->rb);
	if (rb) {
		if (!refcount_inc_not_zero(&rb->refcount))
			rb = NULL;
	}
	rcu_read_unlock();

	return rb;
}