#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {unsigned int csum; } ;
struct cxgbi_sock {scalar_t__ wr_cred; scalar_t__ wr_una_cred; scalar_t__ wr_max_cred; unsigned int snd_una; int /*<<< orphan*/  lock; TYPE_1__* cdev; int /*<<< orphan*/  write_queue; int /*<<< orphan*/  dst; int /*<<< orphan*/  tid; int /*<<< orphan*/  flags; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {scalar_t__ (* csk_push_tx_frames ) (struct cxgbi_sock*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int CXGBI_DBG_SOCK ; 
 int CXGBI_DBG_TOE ; 
 int before (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  cxgbi_conn_tx_open (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  cxgbi_sock_check_wr_invariants (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  cxgbi_sock_dequeue_wr (struct cxgbi_sock*) ; 
 struct sk_buff* cxgbi_sock_peek_wr (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  dst_confirm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  log_debug (int,char*,struct cxgbi_sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,scalar_t__,scalar_t__,unsigned int,int) ; 
 int /*<<< orphan*/  pr_err (char*,struct cxgbi_sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pr_warn (char*,struct cxgbi_sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,...) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct cxgbi_sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

void cxgbi_sock_rcv_wr_ack(struct cxgbi_sock *csk, unsigned int credits,
			   unsigned int snd_una, int seq_chk)
{
	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
			"csk 0x%p,%u,0x%lx,%u, cr %u,%u+%u, snd_una %u,%d.\n",
			csk, csk->state, csk->flags, csk->tid, credits,
			csk->wr_cred, csk->wr_una_cred, snd_una, seq_chk);

	spin_lock_bh(&csk->lock);

	csk->wr_cred += credits;
	if (csk->wr_una_cred > csk->wr_max_cred - csk->wr_cred)
		csk->wr_una_cred = csk->wr_max_cred - csk->wr_cred;

	while (credits) {
		struct sk_buff *p = cxgbi_sock_peek_wr(csk);

		if (unlikely(!p)) {
			pr_err("csk 0x%p,%u,0x%lx,%u, cr %u,%u+%u, empty.\n",
				csk, csk->state, csk->flags, csk->tid, credits,
				csk->wr_cred, csk->wr_una_cred);
			break;
		}

		if (unlikely(credits < p->csum)) {
			pr_warn("csk 0x%p,%u,0x%lx,%u, cr %u,%u+%u, < %u.\n",
				csk, csk->state, csk->flags, csk->tid,
				credits, csk->wr_cred, csk->wr_una_cred,
				p->csum);
			p->csum -= credits;
			break;
		} else {
			cxgbi_sock_dequeue_wr(csk);
			credits -= p->csum;
			kfree_skb(p);
		}
	}

	cxgbi_sock_check_wr_invariants(csk);

	if (seq_chk) {
		if (unlikely(before(snd_una, csk->snd_una))) {
			pr_warn("csk 0x%p,%u,0x%lx,%u, snd_una %u/%u.",
				csk, csk->state, csk->flags, csk->tid, snd_una,
				csk->snd_una);
			goto done;
		}

		if (csk->snd_una != snd_una) {
			csk->snd_una = snd_una;
			dst_confirm(csk->dst);
		}
	}

	if (skb_queue_len(&csk->write_queue)) {
		if (csk->cdev->csk_push_tx_frames(csk, 0))
			cxgbi_conn_tx_open(csk);
	} else
		cxgbi_conn_tx_open(csk);
done:
	spin_unlock_bh(&csk->lock);
}