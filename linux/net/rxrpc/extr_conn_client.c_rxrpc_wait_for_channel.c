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
struct rxrpc_call {int /*<<< orphan*/  waitq; int /*<<< orphan*/  flags; scalar_t__ call_id; int /*<<< orphan*/  debug_id; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  RXRPC_CALL_IS_INTR ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 int /*<<< orphan*/  add_wait_queue_exclusive (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  gfpflags_allow_blocking (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  myself ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rxrpc_wait_for_channel(struct rxrpc_call *call, gfp_t gfp)
{
	int ret = 0;

	_enter("%d", call->debug_id);

	if (!call->call_id) {
		DECLARE_WAITQUEUE(myself, current);

		if (!gfpflags_allow_blocking(gfp)) {
			ret = -EAGAIN;
			goto out;
		}

		add_wait_queue_exclusive(&call->waitq, &myself);
		for (;;) {
			if (test_bit(RXRPC_CALL_IS_INTR, &call->flags))
				set_current_state(TASK_INTERRUPTIBLE);
			else
				set_current_state(TASK_UNINTERRUPTIBLE);
			if (call->call_id)
				break;
			if (test_bit(RXRPC_CALL_IS_INTR, &call->flags) &&
			    signal_pending(current)) {
				ret = -ERESTARTSYS;
				break;
			}
			schedule();
		}
		remove_wait_queue(&call->waitq, &myself);
		__set_current_state(TASK_RUNNING);
	}

	/* Paired with the write barrier in rxrpc_activate_one_channel(). */
	smp_rmb();

out:
	_leave(" = %d", ret);
	return ret;
}