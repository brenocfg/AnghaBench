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
typedef  int /*<<< orphan*/  wait_queue_head_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_wait_queue_exclusive (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fscache_object_cong_wait ; 
 int fscache_object_congested () ; 
 long schedule_timeout (long) ; 
 int /*<<< orphan*/ * this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 

bool fscache_object_sleep_till_congested(signed long *timeoutp)
{
	wait_queue_head_t *cong_wq = this_cpu_ptr(&fscache_object_cong_wait);
	DEFINE_WAIT(wait);

	if (fscache_object_congested())
		return true;

	add_wait_queue_exclusive(cong_wq, &wait);
	if (!fscache_object_congested())
		*timeoutp = schedule_timeout(*timeoutp);
	finish_wait(cong_wq, &wait);

	return fscache_object_congested();
}