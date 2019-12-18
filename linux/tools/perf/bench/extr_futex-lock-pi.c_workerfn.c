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
struct worker {unsigned long ops; int /*<<< orphan*/  futex; int /*<<< orphan*/  tid; } ;

/* Variables and functions */
 scalar_t__ done ; 
 int /*<<< orphan*/  futex_flag ; 
 int futex_lock_pi (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int futex_unlock_pi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  silent ; 
 int /*<<< orphan*/  thread_lock ; 
 int /*<<< orphan*/  thread_parent ; 
 int /*<<< orphan*/  thread_worker ; 
 int /*<<< orphan*/  threads_starting ; 
 int /*<<< orphan*/  usleep (int) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void *workerfn(void *arg)
{
	struct worker *w = (struct worker *) arg;
	unsigned long ops = w->ops;

	pthread_mutex_lock(&thread_lock);
	threads_starting--;
	if (!threads_starting)
		pthread_cond_signal(&thread_parent);
	pthread_cond_wait(&thread_worker, &thread_lock);
	pthread_mutex_unlock(&thread_lock);

	do {
		int ret;
	again:
		ret = futex_lock_pi(w->futex, NULL, futex_flag);

		if (ret) { /* handle lock acquisition */
			if (!silent)
				warn("thread %d: Could not lock pi-lock for %p (%d)",
				     w->tid, w->futex, ret);
			if (done)
				break;

			goto again;
		}

		usleep(1);
		ret = futex_unlock_pi(w->futex, futex_flag);
		if (ret && !silent)
			warn("thread %d: Could not unlock pi-lock for %p (%d)",
			     w->tid, w->futex, ret);
		ops++; /* account for thread's share of work */
	}  while (!done);

	w->ops = ops;
	return NULL;
}