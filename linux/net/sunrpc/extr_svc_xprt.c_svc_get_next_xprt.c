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
struct svc_xprt {int dummy; } ;
struct TYPE_4__ {int thread_wait; } ;
struct svc_rqst {struct svc_xprt* rq_xprt; TYPE_2__ rq_chandle; int /*<<< orphan*/  rq_flags; struct svc_pool* rq_pool; } ;
struct TYPE_3__ {int /*<<< orphan*/  threads_timedout; } ;
struct svc_pool {int /*<<< orphan*/  sp_flags; TYPE_1__ sp_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EINTR ; 
 struct svc_xprt* ERR_PTR (int /*<<< orphan*/ ) ; 
 int HZ ; 
 int /*<<< orphan*/  RQ_BUSY ; 
 int /*<<< orphan*/  SP_CONGESTED ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  WARN_ON_ONCE (struct svc_xprt*) ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ kthread_should_stop () ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rqst_should_sleep (struct svc_rqst*) ; 
 long schedule_timeout (long) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signalled () ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 
 void* svc_xprt_dequeue (struct svc_pool*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_svc_xprt_dequeue (struct svc_rqst*) ; 
 int /*<<< orphan*/  try_to_freeze () ; 

__attribute__((used)) static struct svc_xprt *svc_get_next_xprt(struct svc_rqst *rqstp, long timeout)
{
	struct svc_pool		*pool = rqstp->rq_pool;
	long			time_left = 0;

	/* rq_xprt should be clear on entry */
	WARN_ON_ONCE(rqstp->rq_xprt);

	rqstp->rq_xprt = svc_xprt_dequeue(pool);
	if (rqstp->rq_xprt)
		goto out_found;

	/*
	 * We have to be able to interrupt this wait
	 * to bring down the daemons ...
	 */
	set_current_state(TASK_INTERRUPTIBLE);
	smp_mb__before_atomic();
	clear_bit(SP_CONGESTED, &pool->sp_flags);
	clear_bit(RQ_BUSY, &rqstp->rq_flags);
	smp_mb__after_atomic();

	if (likely(rqst_should_sleep(rqstp)))
		time_left = schedule_timeout(timeout);
	else
		__set_current_state(TASK_RUNNING);

	try_to_freeze();

	set_bit(RQ_BUSY, &rqstp->rq_flags);
	smp_mb__after_atomic();
	rqstp->rq_xprt = svc_xprt_dequeue(pool);
	if (rqstp->rq_xprt)
		goto out_found;

	if (!time_left)
		atomic_long_inc(&pool->sp_stats.threads_timedout);

	if (signalled() || kthread_should_stop())
		return ERR_PTR(-EINTR);
	return ERR_PTR(-EAGAIN);
out_found:
	/* Normally we will wait up to 5 seconds for any required
	 * cache information to be provided.
	 */
	if (!test_bit(SP_CONGESTED, &pool->sp_flags))
		rqstp->rq_chandle.thread_wait = 5*HZ;
	else
		rqstp->rq_chandle.thread_wait = 1*HZ;
	trace_svc_xprt_dequeue(rqstp);
	return rqstp->rq_xprt;
}