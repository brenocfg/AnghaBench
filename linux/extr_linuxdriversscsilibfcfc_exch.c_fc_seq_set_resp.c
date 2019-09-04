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
struct fc_seq {int dummy; } ;
struct fc_exch {scalar_t__ resp_task; void (* resp ) (struct fc_seq*,struct fc_frame*,void*) ;int /*<<< orphan*/  ex_lock; void* arg; int /*<<< orphan*/  resp_wq; scalar_t__ resp_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 scalar_t__ current ; 
 struct fc_exch* fc_seq_exch (struct fc_seq*) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 

void fc_seq_set_resp(struct fc_seq *sp,
		     void (*resp)(struct fc_seq *, struct fc_frame *, void *),
		     void *arg)
{
	struct fc_exch *ep = fc_seq_exch(sp);
	DEFINE_WAIT(wait);

	spin_lock_bh(&ep->ex_lock);
	while (ep->resp_active && ep->resp_task != current) {
		prepare_to_wait(&ep->resp_wq, &wait, TASK_UNINTERRUPTIBLE);
		spin_unlock_bh(&ep->ex_lock);

		schedule();

		spin_lock_bh(&ep->ex_lock);
	}
	finish_wait(&ep->resp_wq, &wait);
	ep->resp = resp;
	ep->arg = arg;
	spin_unlock_bh(&ep->ex_lock);
}