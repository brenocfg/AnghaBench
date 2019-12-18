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
struct pktgen_thread {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pktgen_thread_lock ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ thread_is_running (struct pktgen_thread*) ; 

__attribute__((used)) static int pktgen_wait_thread_run(struct pktgen_thread *t)
{
	while (thread_is_running(t)) {

		/* note: 't' will still be around even after the unlock/lock
		 * cycle because pktgen_thread threads are only cleared at
		 * net exit
		 */
		mutex_unlock(&pktgen_thread_lock);
		msleep_interruptible(100);
		mutex_lock(&pktgen_thread_lock);

		if (signal_pending(current))
			goto signal;
	}
	return 1;
signal:
	return 0;
}