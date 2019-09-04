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
struct worker {unsigned long ops; int /*<<< orphan*/ * futex; } ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  done ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  futex_flag ; 
 int futex_wait (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int nfutexes ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  silent ; 
 int /*<<< orphan*/  thread_lock ; 
 int /*<<< orphan*/  thread_parent ; 
 int /*<<< orphan*/  thread_worker ; 
 int /*<<< orphan*/  threads_starting ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static void *workerfn(void *arg)
{
	int ret;
	struct worker *w = (struct worker *) arg;
	unsigned int i;
	unsigned long ops = w->ops; /* avoid cacheline bouncing */

	pthread_mutex_lock(&thread_lock);
	threads_starting--;
	if (!threads_starting)
		pthread_cond_signal(&thread_parent);
	pthread_cond_wait(&thread_worker, &thread_lock);
	pthread_mutex_unlock(&thread_lock);

	do {
		for (i = 0; i < nfutexes; i++, ops++) {
			/*
			 * We want the futex calls to fail in order to stress
			 * the hashing of uaddr and not measure other steps,
			 * such as internal waitqueue handling, thus enlarging
			 * the critical region protected by hb->lock.
			 */
			ret = futex_wait(&w->futex[i], 1234, NULL, futex_flag);
			if (!silent &&
			    (!ret || errno != EAGAIN || errno != EWOULDBLOCK))
				warn("Non-expected futex return call");
		}
	}  while (!done);

	w->ops = ops;
	return NULL;
}