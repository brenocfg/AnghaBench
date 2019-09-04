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
struct fc_frame {int dummy; } ;
struct fc_exch {scalar_t__ resp_active; void (* resp ) (struct fc_seq*,struct fc_frame*,void*) ;int /*<<< orphan*/  resp_wq; int /*<<< orphan*/  ex_lock; int /*<<< orphan*/ * resp_task; void* arg; } ;

/* Variables and functions */
 int /*<<< orphan*/ * current ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool fc_invoke_resp(struct fc_exch *ep, struct fc_seq *sp,
			   struct fc_frame *fp)
{
	void (*resp)(struct fc_seq *, struct fc_frame *fp, void *arg);
	void *arg;
	bool res = false;

	spin_lock_bh(&ep->ex_lock);
	ep->resp_active++;
	if (ep->resp_task != current)
		ep->resp_task = !ep->resp_task ? current : NULL;
	resp = ep->resp;
	arg = ep->arg;
	spin_unlock_bh(&ep->ex_lock);

	if (resp) {
		resp(sp, fp, arg);
		res = true;
	}

	spin_lock_bh(&ep->ex_lock);
	if (--ep->resp_active == 0)
		ep->resp_task = NULL;
	spin_unlock_bh(&ep->ex_lock);

	if (ep->resp_active == 0)
		wake_up(&ep->resp_wq);

	return res;
}