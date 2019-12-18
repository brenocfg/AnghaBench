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
struct rpc_xprt {int /*<<< orphan*/  sending; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  XPRT_LOCKED ; 
 int /*<<< orphan*/  XPRT_WRITE_SPACE ; 
 int /*<<< orphan*/  __xprt_lock_write_func ; 
 scalar_t__ rpc_wake_up_first_on_wq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct rpc_xprt*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprt_clear_locked (struct rpc_xprt*) ; 
 int /*<<< orphan*/  xprtiod_workqueue ; 

__attribute__((used)) static void __xprt_lock_write_next(struct rpc_xprt *xprt)
{
	if (test_and_set_bit(XPRT_LOCKED, &xprt->state))
		return;
	if (test_bit(XPRT_WRITE_SPACE, &xprt->state))
		goto out_unlock;
	if (rpc_wake_up_first_on_wq(xprtiod_workqueue, &xprt->sending,
				__xprt_lock_write_func, xprt))
		return;
out_unlock:
	xprt_clear_locked(xprt);
}