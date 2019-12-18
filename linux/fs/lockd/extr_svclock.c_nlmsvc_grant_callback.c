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
struct rpc_task {scalar_t__ tk_status; } ;
struct nlm_rqst {struct nlm_block* a_block; } ;
struct nlm_block {int /*<<< orphan*/  b_daemon; int /*<<< orphan*/  b_list; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlm_blocked_lock ; 
 int /*<<< orphan*/  nlmsvc_insert_block_locked (struct nlm_block*,unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_wake_up (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nlmsvc_grant_callback(struct rpc_task *task, void *data)
{
	struct nlm_rqst		*call = data;
	struct nlm_block	*block = call->a_block;
	unsigned long		timeout;

	dprintk("lockd: GRANT_MSG RPC callback\n");

	spin_lock(&nlm_blocked_lock);
	/* if the block is not on a list at this point then it has
	 * been invalidated. Don't try to requeue it.
	 *
	 * FIXME: it's possible that the block is removed from the list
	 * after this check but before the nlmsvc_insert_block. In that
	 * case it will be added back. Perhaps we need better locking
	 * for nlm_blocked?
	 */
	if (list_empty(&block->b_list))
		goto out;

	/* Technically, we should down the file semaphore here. Since we
	 * move the block towards the head of the queue only, no harm
	 * can be done, though. */
	if (task->tk_status < 0) {
		/* RPC error: Re-insert for retransmission */
		timeout = 10 * HZ;
	} else {
		/* Call was successful, now wait for client callback */
		timeout = 60 * HZ;
	}
	nlmsvc_insert_block_locked(block, timeout);
	svc_wake_up(block->b_daemon);
out:
	spin_unlock(&nlm_blocked_lock);
}