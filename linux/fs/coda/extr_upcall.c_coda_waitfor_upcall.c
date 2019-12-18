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
struct venus_comm {int /*<<< orphan*/  vc_mutex; } ;
struct upc_req {int uc_flags; int /*<<< orphan*/  uc_sleep; int /*<<< orphan*/  uc_chain; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 scalar_t__ CODA_INTERRUPTIBLE (struct upc_req*) ; 
 int CODA_REQ_ABORT ; 
 int CODA_REQ_WRITE ; 
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long HZ ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  coda_block_signals (int /*<<< orphan*/ *) ; 
 unsigned long coda_timeout ; 
 int /*<<< orphan*/  coda_unblock_signals (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  schedule_timeout (unsigned long) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static inline void coda_waitfor_upcall(struct venus_comm *vcp,
				       struct upc_req *req)
{
	DECLARE_WAITQUEUE(wait, current);
	unsigned long timeout = jiffies + coda_timeout * HZ;
	sigset_t old;
	int blocked;

	coda_block_signals(&old);
	blocked = 1;

	add_wait_queue(&req->uc_sleep, &wait);
	for (;;) {
		if (CODA_INTERRUPTIBLE(req))
			set_current_state(TASK_INTERRUPTIBLE);
		else
			set_current_state(TASK_UNINTERRUPTIBLE);

		/* got a reply */
		if (req->uc_flags & (CODA_REQ_WRITE | CODA_REQ_ABORT))
			break;

		if (blocked && time_after(jiffies, timeout) &&
		    CODA_INTERRUPTIBLE(req))
		{
			coda_unblock_signals(&old);
			blocked = 0;
		}

		if (signal_pending(current)) {
			list_del(&req->uc_chain);
			break;
		}

		mutex_unlock(&vcp->vc_mutex);
		if (blocked)
			schedule_timeout(HZ);
		else
			schedule();
		mutex_lock(&vcp->vc_mutex);
	}
	if (blocked)
		coda_unblock_signals(&old);

	remove_wait_queue(&req->uc_sleep, &wait);
	set_current_state(TASK_RUNNING);
}