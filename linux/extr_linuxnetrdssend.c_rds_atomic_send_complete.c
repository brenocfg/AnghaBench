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
struct rm_atomic_op {struct rds_notifier* op_notifier; scalar_t__ op_notify; scalar_t__ op_active; } ;
struct rds_sock {int /*<<< orphan*/  rs_lock; int /*<<< orphan*/  rs_notify_queue; } ;
struct rds_notifier {int n_status; int /*<<< orphan*/  n_list; } ;
struct rds_message {int /*<<< orphan*/  m_rs_lock; struct rds_sock* m_rs; int /*<<< orphan*/  m_flags; struct rm_atomic_op atomic; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDS_MSG_ON_SOCK ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_rs_to_sk (struct rds_sock*) ; 
 int /*<<< orphan*/  rds_wake_sk_sleep (struct rds_sock*) ; 
 int /*<<< orphan*/  sock_hold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rds_atomic_send_complete(struct rds_message *rm, int status)
{
	struct rds_sock *rs = NULL;
	struct rm_atomic_op *ao;
	struct rds_notifier *notifier;
	unsigned long flags;

	spin_lock_irqsave(&rm->m_rs_lock, flags);

	ao = &rm->atomic;
	if (test_bit(RDS_MSG_ON_SOCK, &rm->m_flags)
	    && ao->op_active && ao->op_notify && ao->op_notifier) {
		notifier = ao->op_notifier;
		rs = rm->m_rs;
		sock_hold(rds_rs_to_sk(rs));

		notifier->n_status = status;
		spin_lock(&rs->rs_lock);
		list_add_tail(&notifier->n_list, &rs->rs_notify_queue);
		spin_unlock(&rs->rs_lock);

		ao->op_notifier = NULL;
	}

	spin_unlock_irqrestore(&rm->m_rs_lock, flags);

	if (rs) {
		rds_wake_sk_sleep(rs);
		sock_put(rds_rs_to_sk(rs));
	}
}