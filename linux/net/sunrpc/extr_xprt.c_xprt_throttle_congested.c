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
struct rpc_xprt {int /*<<< orphan*/  reserve_lock; int /*<<< orphan*/  backlog; int /*<<< orphan*/  state; } ;
struct rpc_task {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XPRT_CONGESTED ; 
 int /*<<< orphan*/  rpc_sleep_on (int /*<<< orphan*/ *,struct rpc_task*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool xprt_throttle_congested(struct rpc_xprt *xprt, struct rpc_task *task)
{
	bool ret = false;

	if (!test_bit(XPRT_CONGESTED, &xprt->state))
		goto out;
	spin_lock(&xprt->reserve_lock);
	if (test_bit(XPRT_CONGESTED, &xprt->state)) {
		rpc_sleep_on(&xprt->backlog, task, NULL);
		ret = true;
	}
	spin_unlock(&xprt->reserve_lock);
out:
	return ret;
}