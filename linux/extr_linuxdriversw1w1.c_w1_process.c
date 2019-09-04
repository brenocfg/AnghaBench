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
struct w1_master {int /*<<< orphan*/  refcnt; scalar_t__ search_count; int /*<<< orphan*/  list_mutex; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  W1_SEARCH ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 unsigned long schedule_timeout (unsigned long) ; 
 unsigned long usecs_to_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  w1_process_callbacks (struct w1_master*) ; 
 int /*<<< orphan*/  w1_search_process (struct w1_master*,int /*<<< orphan*/ ) ; 
 int w1_timeout ; 
 scalar_t__ w1_timeout_us ; 

int w1_process(void *data)
{
	struct w1_master *dev = (struct w1_master *) data;
	/* As long as w1_timeout is only set by a module parameter the sleep
	 * time can be calculated in jiffies once.
	 */
	const unsigned long jtime =
	  usecs_to_jiffies(w1_timeout * 1000000 + w1_timeout_us);
	/* remainder if it woke up early */
	unsigned long jremain = 0;

	for (;;) {

		if (!jremain && dev->search_count) {
			mutex_lock(&dev->mutex);
			w1_search_process(dev, W1_SEARCH);
			mutex_unlock(&dev->mutex);
		}

		mutex_lock(&dev->list_mutex);
		/* Note, w1_process_callback drops the lock while processing,
		 * but locks it again before returning.
		 */
		if (!w1_process_callbacks(dev) && jremain) {
			/* a wake up is either to stop the thread, process
			 * callbacks, or search, it isn't process callbacks, so
			 * schedule a search.
			 */
			jremain = 1;
		}

		__set_current_state(TASK_INTERRUPTIBLE);

		/* hold list_mutex until after interruptible to prevent loosing
		 * the wakeup signal when async_cmd is added.
		 */
		mutex_unlock(&dev->list_mutex);

		if (kthread_should_stop())
			break;

		/* Only sleep when the search is active. */
		if (dev->search_count) {
			if (!jremain)
				jremain = jtime;
			jremain = schedule_timeout(jremain);
		}
		else
			schedule();
	}

	atomic_dec(&dev->refcnt);

	return 0;
}