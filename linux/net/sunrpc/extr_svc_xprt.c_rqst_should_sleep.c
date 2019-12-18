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
struct svc_rqst {struct svc_pool* rq_pool; } ;
struct svc_pool {int /*<<< orphan*/  sp_sockets; int /*<<< orphan*/  sp_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SP_TASK_PENDING ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ freezing (int /*<<< orphan*/ ) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ signalled () ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
rqst_should_sleep(struct svc_rqst *rqstp)
{
	struct svc_pool		*pool = rqstp->rq_pool;

	/* did someone call svc_wake_up? */
	if (test_and_clear_bit(SP_TASK_PENDING, &pool->sp_flags))
		return false;

	/* was a socket queued? */
	if (!list_empty(&pool->sp_sockets))
		return false;

	/* are we shutting down? */
	if (signalled() || kthread_should_stop())
		return false;

	/* are we freezing? */
	if (freezing(current))
		return false;

	return true;
}