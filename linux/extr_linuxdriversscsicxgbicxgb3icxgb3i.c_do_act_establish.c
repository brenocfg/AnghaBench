#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct t3cdev {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  csum; } ;
struct TYPE_4__ {int /*<<< orphan*/ * function; } ;
struct cxgbi_sock {scalar_t__ state; unsigned int tid; int rcv_win; int /*<<< orphan*/  lock; int /*<<< orphan*/  write_queue; int /*<<< orphan*/  rcv_wup; int /*<<< orphan*/  rcv_nxt; int /*<<< orphan*/  copied_seq; int /*<<< orphan*/  flags; TYPE_2__ retry_timer; int /*<<< orphan*/  rss_qid; TYPE_1__* cdev; } ;
struct cpl_act_establish {int /*<<< orphan*/  tcp_opt; int /*<<< orphan*/  snd_isn; int /*<<< orphan*/  rcv_isn; int /*<<< orphan*/  tos_tid; } ;
struct TYPE_3__ {int /*<<< orphan*/  lldev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTPF_ACTIVE_CLOSE_NEEDED ; 
 int /*<<< orphan*/  CTPF_HAS_TID ; 
 scalar_t__ CTP_ACTIVE_OPEN ; 
 int CXGBI_DBG_SOCK ; 
 int CXGBI_DBG_TOE ; 
 unsigned int GET_TID (struct cpl_act_establish*) ; 
 unsigned int G_PASS_OPEN_TID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_QNUM (int /*<<< orphan*/ ) ; 
 int M_RCV_BUFSIZ ; 
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 struct cpl_act_establish* cplhdr (struct sk_buff*) ; 
 int /*<<< orphan*/  cxgb3_insert_tid (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct cxgbi_sock*,unsigned int) ; 
 int /*<<< orphan*/  cxgbi_conn_tx_open (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  cxgbi_sock_established (struct cxgbi_sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cxgbi_sock_flag (struct cxgbi_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgbi_sock_get (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  cxgbi_sock_set_flag (struct cxgbi_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  free_atid (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  log_debug (int,char*,unsigned int,unsigned int,struct cxgbi_sock*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,struct cxgbi_sock*,scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  push_tx_frames (struct cxgbi_sock*,int) ; 
 int /*<<< orphan*/  send_abort_req (struct cxgbi_sock*) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t3_client ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int do_act_establish(struct t3cdev *tdev, struct sk_buff *skb, void *ctx)
{
	struct cxgbi_sock *csk = ctx;
	struct cpl_act_establish *req = cplhdr(skb);
	unsigned int tid = GET_TID(req);
	unsigned int atid = G_PASS_OPEN_TID(ntohl(req->tos_tid));
	u32 rcv_isn = ntohl(req->rcv_isn);	/* real RCV_ISN + 1 */

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"atid 0x%x,tid 0x%x, csk 0x%p,%u,0x%lx, isn %u.\n",
		atid, atid, csk, csk->state, csk->flags, rcv_isn);

	cxgbi_sock_get(csk);
	cxgbi_sock_set_flag(csk, CTPF_HAS_TID);
	csk->tid = tid;
	cxgb3_insert_tid(csk->cdev->lldev, &t3_client, csk, tid);

	free_atid(csk);

	csk->rss_qid = G_QNUM(ntohs(skb->csum));

	spin_lock_bh(&csk->lock);
	if (csk->retry_timer.function) {
		del_timer(&csk->retry_timer);
		csk->retry_timer.function = NULL;
	}

	if (unlikely(csk->state != CTP_ACTIVE_OPEN))
		pr_info("csk 0x%p,%u,0x%lx,%u, got EST.\n",
			csk, csk->state, csk->flags, csk->tid);

	csk->copied_seq = csk->rcv_wup = csk->rcv_nxt = rcv_isn;
	if (csk->rcv_win > (M_RCV_BUFSIZ << 10))
		csk->rcv_wup -= csk->rcv_win - (M_RCV_BUFSIZ << 10);

	cxgbi_sock_established(csk, ntohl(req->snd_isn), ntohs(req->tcp_opt));

	if (unlikely(cxgbi_sock_flag(csk, CTPF_ACTIVE_CLOSE_NEEDED)))
		/* upper layer has requested closing */
		send_abort_req(csk);
	else {
		if (skb_queue_len(&csk->write_queue))
			push_tx_frames(csk, 1);
		cxgbi_conn_tx_open(csk);
	}

	spin_unlock_bh(&csk->lock);
	__kfree_skb(skb);
	return 0;
}