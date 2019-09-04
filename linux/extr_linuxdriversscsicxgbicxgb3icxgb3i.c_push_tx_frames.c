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
struct tx_data_wr {int dummy; } ;
struct sk_buff {int len; int data_len; int csum; scalar_t__ truesize; int /*<<< orphan*/  priority; } ;
struct cxgbi_sock {scalar_t__ state; int wr_cred; int wr_una_cred; int wr_max_cred; int snd_nxt; int /*<<< orphan*/  l2t; TYPE_1__* cdev; int /*<<< orphan*/  tid; int /*<<< orphan*/  write_queue; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int nr_frags; } ;
struct TYPE_3__ {int /*<<< orphan*/  lldev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPL_PRIORITY_DATA ; 
 scalar_t__ CTP_ABORTING ; 
 scalar_t__ CTP_CLOSE_WAIT_1 ; 
 scalar_t__ CTP_ESTABLISHED ; 
 int CXGBI_DBG_PDU_TX ; 
 int CXGBI_DBG_TOE ; 
 int SKB_WR_LIST_SIZE ; 
 int /*<<< orphan*/  SKCBF_TX_NEED_HDR ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __skb_unlink (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arp_failure_skb_discard ; 
 int /*<<< orphan*/  cxgbi_skcb_clear_flag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgbi_skcb_test_flag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgbi_skcb_ulp_mode (struct sk_buff*) ; 
 int /*<<< orphan*/  cxgbi_sock_enqueue_wr (struct cxgbi_sock*,struct sk_buff*) ; 
 scalar_t__ cxgbi_ulp_extra_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2t_send (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (int,char*,struct cxgbi_sock*,scalar_t__,...) ; 
 int /*<<< orphan*/  make_tx_data_wr (struct cxgbi_sock*,struct sk_buff*,int,int) ; 
 int /*<<< orphan*/  set_arp_failure_handler (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ *) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int* skb_wrs ; 
 scalar_t__ unlikely (int) ; 
 int wrlen ; 

__attribute__((used)) static int push_tx_frames(struct cxgbi_sock *csk, int req_completion)
{
	int total_size = 0;
	struct sk_buff *skb;

	if (unlikely(csk->state < CTP_ESTABLISHED ||
		csk->state == CTP_CLOSE_WAIT_1 || csk->state >= CTP_ABORTING)) {
			log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_PDU_TX,
				"csk 0x%p,%u,0x%lx,%u, in closing state.\n",
				csk, csk->state, csk->flags, csk->tid);
		return 0;
	}

	while (csk->wr_cred && (skb = skb_peek(&csk->write_queue)) != NULL) {
		int len = skb->len;	/* length before skb_push */
		int frags = skb_shinfo(skb)->nr_frags + (len != skb->data_len);
		int wrs_needed = skb_wrs[frags];

		if (wrs_needed > 1 && len + sizeof(struct tx_data_wr) <= wrlen)
			wrs_needed = 1;

		WARN_ON(frags >= SKB_WR_LIST_SIZE || wrs_needed < 1);

		if (csk->wr_cred < wrs_needed) {
			log_debug(1 << CXGBI_DBG_PDU_TX,
				"csk 0x%p, skb len %u/%u, frag %u, wr %d<%u.\n",
				csk, skb->len, skb->data_len, frags,
				wrs_needed, csk->wr_cred);
			break;
		}

		__skb_unlink(skb, &csk->write_queue);
		skb->priority = CPL_PRIORITY_DATA;
		skb->csum = wrs_needed;	/* remember this until the WR_ACK */
		csk->wr_cred -= wrs_needed;
		csk->wr_una_cred += wrs_needed;
		cxgbi_sock_enqueue_wr(csk, skb);

		log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_PDU_TX,
			"csk 0x%p, enqueue, skb len %u/%u, frag %u, wr %d, "
			"left %u, unack %u.\n",
			csk, skb->len, skb->data_len, frags, skb->csum,
			csk->wr_cred, csk->wr_una_cred);

		if (likely(cxgbi_skcb_test_flag(skb, SKCBF_TX_NEED_HDR))) {
			if ((req_completion &&
				csk->wr_una_cred == wrs_needed) ||
			     csk->wr_una_cred >= csk->wr_max_cred / 2) {
				req_completion = 1;
				csk->wr_una_cred = 0;
			}
			len += cxgbi_ulp_extra_len(cxgbi_skcb_ulp_mode(skb));
			make_tx_data_wr(csk, skb, len, req_completion);
			csk->snd_nxt += len;
			cxgbi_skcb_clear_flag(skb, SKCBF_TX_NEED_HDR);
		}
		total_size += skb->truesize;
		log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_PDU_TX,
			"csk 0x%p, tid 0x%x, send skb 0x%p.\n",
			csk, csk->tid, skb);
		set_arp_failure_handler(skb, arp_failure_skb_discard);
		l2t_send(csk->cdev->lldev, skb, csk->l2t);
	}
	return total_size;
}