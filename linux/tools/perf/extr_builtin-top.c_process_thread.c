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
struct TYPE_2__ {int rotate; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; struct ordered_events* in; } ;
struct perf_top {TYPE_1__ qe; } ;
struct ordered_events {int /*<<< orphan*/  nr_events; } ;

/* Variables and functions */
 int /*<<< orphan*/  OE_FLUSH__TOP ; 
 int /*<<< orphan*/  done ; 
 scalar_t__ ordered_events__flush (struct ordered_events*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ordered_events* rotate_queues (struct perf_top*) ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static void *process_thread(void *arg)
{
	struct perf_top *top = arg;

	while (!done) {
		struct ordered_events *out, *in = top->qe.in;

		if (!in->nr_events) {
			usleep(100);
			continue;
		}

		out = rotate_queues(top);

		pthread_mutex_lock(&top->qe.mutex);
		top->qe.rotate = true;
		pthread_cond_wait(&top->qe.cond, &top->qe.mutex);
		pthread_mutex_unlock(&top->qe.mutex);

		if (ordered_events__flush(out, OE_FLUSH__TOP))
			pr_err("failed to process events\n");
	}

	return NULL;
}