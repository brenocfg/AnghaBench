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
struct cpu_stopper {int /*<<< orphan*/  lock; int /*<<< orphan*/  enabled; } ;
struct cpu_stop_work {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAKE_Q (int /*<<< orphan*/ ) ; 
 int EDEADLK ; 
 int ENOENT ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int /*<<< orphan*/  __cpu_stop_queue_work (struct cpu_stopper*,struct cpu_stop_work*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  cpu_stopper ; 
 struct cpu_stopper* per_cpu_ptr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  raw_spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int stop_cpus_in_progress ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_up_q (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeq ; 

__attribute__((used)) static int cpu_stop_queue_two_works(int cpu1, struct cpu_stop_work *work1,
				    int cpu2, struct cpu_stop_work *work2)
{
	struct cpu_stopper *stopper1 = per_cpu_ptr(&cpu_stopper, cpu1);
	struct cpu_stopper *stopper2 = per_cpu_ptr(&cpu_stopper, cpu2);
	DEFINE_WAKE_Q(wakeq);
	int err;

retry:
	/*
	 * The waking up of stopper threads has to happen in the same
	 * scheduling context as the queueing.  Otherwise, there is a
	 * possibility of one of the above stoppers being woken up by another
	 * CPU, and preempting us. This will cause us to not wake up the other
	 * stopper forever.
	 */
	preempt_disable();
	raw_spin_lock_irq(&stopper1->lock);
	raw_spin_lock_nested(&stopper2->lock, SINGLE_DEPTH_NESTING);

	if (!stopper1->enabled || !stopper2->enabled) {
		err = -ENOENT;
		goto unlock;
	}

	/*
	 * Ensure that if we race with __stop_cpus() the stoppers won't get
	 * queued up in reverse order leading to system deadlock.
	 *
	 * We can't miss stop_cpus_in_progress if queue_stop_cpus_work() has
	 * queued a work on cpu1 but not on cpu2, we hold both locks.
	 *
	 * It can be falsely true but it is safe to spin until it is cleared,
	 * queue_stop_cpus_work() does everything under preempt_disable().
	 */
	if (unlikely(stop_cpus_in_progress)) {
		err = -EDEADLK;
		goto unlock;
	}

	err = 0;
	__cpu_stop_queue_work(stopper1, work1, &wakeq);
	__cpu_stop_queue_work(stopper2, work2, &wakeq);

unlock:
	raw_spin_unlock(&stopper2->lock);
	raw_spin_unlock_irq(&stopper1->lock);

	if (unlikely(err == -EDEADLK)) {
		preempt_enable();

		while (stop_cpus_in_progress)
			cpu_relax();

		goto retry;
	}

	wake_up_q(&wakeq);
	preempt_enable();

	return err;
}