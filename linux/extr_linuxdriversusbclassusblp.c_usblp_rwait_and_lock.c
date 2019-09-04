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
struct usblp {int /*<<< orphan*/  rwait; int /*<<< orphan*/  mut; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINTR ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int usblp_rtest (struct usblp*,int) ; 
 int /*<<< orphan*/  waita ; 

__attribute__((used)) static int usblp_rwait_and_lock(struct usblp *usblp, int nonblock)
{
	DECLARE_WAITQUEUE(waita, current);
	int rc;

	add_wait_queue(&usblp->rwait, &waita);
	for (;;) {
		if (mutex_lock_interruptible(&usblp->mut)) {
			rc = -EINTR;
			break;
		}
		set_current_state(TASK_INTERRUPTIBLE);
		if ((rc = usblp_rtest(usblp, nonblock)) < 0) {
			mutex_unlock(&usblp->mut);
			break;
		}
		if (rc == 0)	/* Keep it locked */
			break;
		mutex_unlock(&usblp->mut);
		schedule();
	}
	set_current_state(TASK_RUNNING);
	remove_wait_queue(&usblp->rwait, &waita);
	return rc;
}