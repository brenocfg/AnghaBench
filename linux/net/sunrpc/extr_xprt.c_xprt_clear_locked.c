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
struct rpc_xprt {int /*<<< orphan*/  task_cleanup; int /*<<< orphan*/  state; int /*<<< orphan*/ * snd_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  XPRT_CLOSE_WAIT ; 
 int /*<<< orphan*/  XPRT_LOCKED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprtiod_workqueue ; 

__attribute__((used)) static void xprt_clear_locked(struct rpc_xprt *xprt)
{
	xprt->snd_task = NULL;
	if (!test_bit(XPRT_CLOSE_WAIT, &xprt->state)) {
		smp_mb__before_atomic();
		clear_bit(XPRT_LOCKED, &xprt->state);
		smp_mb__after_atomic();
	} else
		queue_work(xprtiod_workqueue, &xprt->task_cleanup);
}