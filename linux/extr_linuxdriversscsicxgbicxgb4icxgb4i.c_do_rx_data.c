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
struct tid_info {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;
struct cxgbi_sock {int /*<<< orphan*/  lock; } ;
struct cxgbi_device {int dummy; } ;
struct cxgb4_lld_info {struct tid_info* tids; } ;
struct cpl_rx_data {int dummy; } ;

/* Variables and functions */
 unsigned int GET_TID (struct cpl_rx_data*) ; 
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 struct cxgb4_lld_info* cxgbi_cdev_priv (struct cxgbi_device*) ; 
 struct cxgbi_sock* lookup_tid (struct tid_info*,unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  send_abort_req (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void do_rx_data(struct cxgbi_device *cdev, struct sk_buff *skb)
{
	struct cxgbi_sock *csk;
	struct cpl_rx_data *cpl = (struct cpl_rx_data *)skb->data;
	unsigned int tid = GET_TID(cpl);
	struct cxgb4_lld_info *lldi = cxgbi_cdev_priv(cdev);
	struct tid_info *t = lldi->tids;

	csk = lookup_tid(t, tid);
	if (!csk) {
		pr_err("can't find connection for tid %u.\n", tid);
	} else {
		/* not expecting this, reset the connection. */
		pr_err("csk 0x%p, tid %u, rcv cpl_rx_data.\n", csk, tid);
		spin_lock_bh(&csk->lock);
		send_abort_req(csk);
		spin_unlock_bh(&csk->lock);
	}
	__kfree_skb(skb);
}