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
struct cxgbi_sock {int /*<<< orphan*/  lock; int /*<<< orphan*/  err; int /*<<< orphan*/  tid; int /*<<< orphan*/  flags; int /*<<< orphan*/  state; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct cxgbi_device {int dummy; } ;
struct cxgb4_lld_info {struct tid_info* tids; } ;
struct cpl_abort_req_rss {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int CPL_ABORT_NO_RST ; 
 int /*<<< orphan*/  CTPF_ABORT_REQ_RCVD ; 
 int /*<<< orphan*/  CTPF_ABORT_RPL_PENDING ; 
 int /*<<< orphan*/  CTPF_TX_DATA_SENT ; 
 int /*<<< orphan*/  CTP_ABORTING ; 
 unsigned int GET_TID (struct cpl_abort_req_rss*) ; 
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  abort_status_to_errno (struct cxgbi_sock*,int /*<<< orphan*/ ,int*) ; 
 struct cxgb4_lld_info* cxgbi_cdev_priv (struct cxgbi_device*) ; 
 int /*<<< orphan*/  cxgbi_sock_clear_flag (struct cxgbi_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgbi_sock_closed (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  cxgbi_sock_flag (struct cxgbi_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgbi_sock_get (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  cxgbi_sock_put (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  cxgbi_sock_set_flag (struct cxgbi_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgbi_sock_set_state (struct cxgbi_sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_neg_adv (int /*<<< orphan*/ ) ; 
 struct cxgbi_sock* lookup_tid (struct tid_info*,unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 
 int /*<<< orphan*/  pr_info_ipaddr (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct cxgbi_sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_abort_rpl (struct cxgbi_sock*,int) ; 
 int /*<<< orphan*/  send_tx_flowc_wr (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void do_abort_req_rss(struct cxgbi_device *cdev, struct sk_buff *skb)
{
	struct cxgbi_sock *csk;
	struct cpl_abort_req_rss *req = (struct cpl_abort_req_rss *)skb->data;
	unsigned int tid = GET_TID(req);
	struct cxgb4_lld_info *lldi = cxgbi_cdev_priv(cdev);
	struct tid_info *t = lldi->tids;
	int rst_status = CPL_ABORT_NO_RST;

	csk = lookup_tid(t, tid);
	if (unlikely(!csk)) {
		pr_err("can't find connection for tid %u.\n", tid);
		goto rel_skb;
	}

	pr_info_ipaddr("csk 0x%p,%u,0x%lx,%u, status %u.\n",
		       (&csk->saddr), (&csk->daddr),
		       csk, csk->state, csk->flags, csk->tid, req->status);

	if (is_neg_adv(req->status))
		goto rel_skb;

	cxgbi_sock_get(csk);
	spin_lock_bh(&csk->lock);

	cxgbi_sock_clear_flag(csk, CTPF_ABORT_REQ_RCVD);

	if (!cxgbi_sock_flag(csk, CTPF_TX_DATA_SENT)) {
		send_tx_flowc_wr(csk);
		cxgbi_sock_set_flag(csk, CTPF_TX_DATA_SENT);
	}

	cxgbi_sock_set_flag(csk, CTPF_ABORT_REQ_RCVD);
	cxgbi_sock_set_state(csk, CTP_ABORTING);

	send_abort_rpl(csk, rst_status);

	if (!cxgbi_sock_flag(csk, CTPF_ABORT_RPL_PENDING)) {
		csk->err = abort_status_to_errno(csk, req->status, &rst_status);
		cxgbi_sock_closed(csk);
	}

	spin_unlock_bh(&csk->lock);
	cxgbi_sock_put(csk);
rel_skb:
	__kfree_skb(skb);
}