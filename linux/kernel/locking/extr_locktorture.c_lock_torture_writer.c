#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lock_stress_stats {int /*<<< orphan*/  n_lock_acquired; int /*<<< orphan*/  n_lock_fail; } ;
struct TYPE_4__ {TYPE_1__* cur_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* task_boost ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* writeunlock ) () ;int /*<<< orphan*/  (* write_delay ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* writelock ) () ;} ;
typedef  int /*<<< orphan*/  DEFINE_TORTURE_RANDOM ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_NICE ; 
 int /*<<< orphan*/  VERBOSE_TOROUT_STRING (char*) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  current ; 
 TYPE_2__ cxt ; 
 int lock_is_read_held ; 
 int lock_is_write_held ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 int /*<<< orphan*/  set_user_nice (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 () ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 () ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stutter_wait (char*) ; 
 int /*<<< orphan*/  torture_kthread_stopping (char*) ; 
 int /*<<< orphan*/  torture_must_stop () ; 
 int torture_random (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lock_torture_writer(void *arg)
{
	struct lock_stress_stats *lwsp = arg;
	static DEFINE_TORTURE_RANDOM(rand);

	VERBOSE_TOROUT_STRING("lock_torture_writer task started");
	set_user_nice(current, MAX_NICE);

	do {
		if ((torture_random(&rand) & 0xfffff) == 0)
			schedule_timeout_uninterruptible(1);

		cxt.cur_ops->task_boost(&rand);
		cxt.cur_ops->writelock();
		if (WARN_ON_ONCE(lock_is_write_held))
			lwsp->n_lock_fail++;
		lock_is_write_held = 1;
		if (WARN_ON_ONCE(lock_is_read_held))
			lwsp->n_lock_fail++; /* rare, but... */

		lwsp->n_lock_acquired++;
		cxt.cur_ops->write_delay(&rand);
		lock_is_write_held = 0;
		cxt.cur_ops->writeunlock();

		stutter_wait("lock_torture_writer");
	} while (!torture_must_stop());

	cxt.cur_ops->task_boost(NULL); /* reset prio */
	torture_kthread_stopping("lock_torture_writer");
	return 0;
}