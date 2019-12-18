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
struct sk_buff_head {int dummy; } ;
struct sock {scalar_t__ sk_state; int /*<<< orphan*/  (* sk_data_ready ) (struct sock*) ;int /*<<< orphan*/  (* sk_write_space ) (struct sock*) ;struct sk_buff_head sk_receive_queue; int /*<<< orphan*/  sk_drops; int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;} ;
struct sk_buff {int /*<<< orphan*/ * dev; } ;
struct pnpipehdr {int message_id; int /*<<< orphan*/  state_after_reset; } ;
struct pep_sock {int init_enable; int /*<<< orphan*/  rx_credits; int /*<<< orphan*/  tx_credits; int /*<<< orphan*/  tx_fc; int /*<<< orphan*/  rx_fc; struct sk_buff_head ctrlreq_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int NET_RX_DROP ; 
 int NET_RX_SUCCESS ; 
 int /*<<< orphan*/  PNPIPE_CTRLREQ_MAX ; 
#define  PNS_PEP_CONNECT_REQ 143 
#define  PNS_PEP_CTRL_REQ 142 
#define  PNS_PEP_DISABLE_REQ 141 
#define  PNS_PEP_DISCONNECT_REQ 140 
#define  PNS_PEP_ENABLE_REQ 139 
#define  PNS_PEP_RESET_REQ 138 
#define  PNS_PEP_STATUS_IND 137 
#define  PNS_PIPE_ALIGNED_DATA 136 
#define  PNS_PIPE_CREATED_IND 135 
#define  PNS_PIPE_DATA 134 
#define  PNS_PIPE_DISABLED_IND 133 
#define  PNS_PIPE_ENABLED_IND 132 
#define  PNS_PIPE_REDIRECTED_IND 131 
#define  PNS_PIPE_RESET_IND 130 
#define  PN_PIPE_DISABLE 129 
#define  PN_PIPE_ENABLE 128 
 int /*<<< orphan*/  PN_PIPE_ERR_PEP_IN_USE ; 
 int /*<<< orphan*/  PN_PIPE_NO_ERROR ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 scalar_t__ TCP_CLOSE_WAIT ; 
 scalar_t__ TCP_ESTABLISHED ; 
 scalar_t__ TCP_SYN_RECV ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  net_dbg_ratelimited (char*,int) ; 
 int /*<<< orphan*/  pep_reject_conn (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pep_reply (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pep_sock* pep_sk (struct sock*) ; 
 int /*<<< orphan*/  pipe_grant_credits (struct sock*,int /*<<< orphan*/ ) ; 
 int pipe_rcv_created (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  pipe_rcv_status (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  pn_flow_safe (int /*<<< orphan*/ ) ; 
 struct pnpipehdr* pnp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_len (struct sk_buff_head*) ; 
 int /*<<< orphan*/  skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_owner_r (struct sk_buff*,struct sock*) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int sock_queue_rcv_skb (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  stub2 (struct sock*) ; 
 int /*<<< orphan*/  stub3 (struct sock*) ; 

__attribute__((used)) static int pipe_do_rcv(struct sock *sk, struct sk_buff *skb)
{
	struct pep_sock *pn = pep_sk(sk);
	struct pnpipehdr *hdr = pnp_hdr(skb);
	struct sk_buff_head *queue;
	int err = 0;

	BUG_ON(sk->sk_state == TCP_CLOSE_WAIT);

	switch (hdr->message_id) {
	case PNS_PEP_CONNECT_REQ:
		pep_reject_conn(sk, skb, PN_PIPE_ERR_PEP_IN_USE, GFP_ATOMIC);
		break;

	case PNS_PEP_DISCONNECT_REQ:
		pep_reply(sk, skb, PN_PIPE_NO_ERROR, NULL, 0, GFP_ATOMIC);
		sk->sk_state = TCP_CLOSE_WAIT;
		if (!sock_flag(sk, SOCK_DEAD))
			sk->sk_state_change(sk);
		break;

	case PNS_PEP_ENABLE_REQ:
		/* Wait for PNS_PIPE_(ENABLED|REDIRECTED)_IND */
		pep_reply(sk, skb, PN_PIPE_NO_ERROR, NULL, 0, GFP_ATOMIC);
		break;

	case PNS_PEP_RESET_REQ:
		switch (hdr->state_after_reset) {
		case PN_PIPE_DISABLE:
			pn->init_enable = 0;
			break;
		case PN_PIPE_ENABLE:
			pn->init_enable = 1;
			break;
		default: /* not allowed to send an error here!? */
			err = -EINVAL;
			goto out;
		}
		/* fall through */
	case PNS_PEP_DISABLE_REQ:
		atomic_set(&pn->tx_credits, 0);
		pep_reply(sk, skb, PN_PIPE_NO_ERROR, NULL, 0, GFP_ATOMIC);
		break;

	case PNS_PEP_CTRL_REQ:
		if (skb_queue_len(&pn->ctrlreq_queue) >= PNPIPE_CTRLREQ_MAX) {
			atomic_inc(&sk->sk_drops);
			break;
		}
		__skb_pull(skb, 4);
		queue = &pn->ctrlreq_queue;
		goto queue;

	case PNS_PIPE_ALIGNED_DATA:
		__skb_pull(skb, 1);
		/* fall through */
	case PNS_PIPE_DATA:
		__skb_pull(skb, 3); /* Pipe data header */
		if (!pn_flow_safe(pn->rx_fc)) {
			err = sock_queue_rcv_skb(sk, skb);
			if (!err)
				return NET_RX_SUCCESS;
			err = -ENOBUFS;
			break;
		}

		if (pn->rx_credits == 0) {
			atomic_inc(&sk->sk_drops);
			err = -ENOBUFS;
			break;
		}
		pn->rx_credits--;
		queue = &sk->sk_receive_queue;
		goto queue;

	case PNS_PEP_STATUS_IND:
		pipe_rcv_status(sk, skb);
		break;

	case PNS_PIPE_REDIRECTED_IND:
		err = pipe_rcv_created(sk, skb);
		break;

	case PNS_PIPE_CREATED_IND:
		err = pipe_rcv_created(sk, skb);
		if (err)
			break;
		/* fall through */
	case PNS_PIPE_RESET_IND:
		if (!pn->init_enable)
			break;
		/* fall through */
	case PNS_PIPE_ENABLED_IND:
		if (!pn_flow_safe(pn->tx_fc)) {
			atomic_set(&pn->tx_credits, 1);
			sk->sk_write_space(sk);
		}
		if (sk->sk_state == TCP_ESTABLISHED)
			break; /* Nothing to do */
		sk->sk_state = TCP_ESTABLISHED;
		pipe_grant_credits(sk, GFP_ATOMIC);
		break;

	case PNS_PIPE_DISABLED_IND:
		sk->sk_state = TCP_SYN_RECV;
		pn->rx_credits = 0;
		break;

	default:
		net_dbg_ratelimited("Phonet unknown PEP message: %u\n",
				    hdr->message_id);
		err = -EINVAL;
	}
out:
	kfree_skb(skb);
	return (err == -ENOBUFS) ? NET_RX_DROP : NET_RX_SUCCESS;

queue:
	skb->dev = NULL;
	skb_set_owner_r(skb, sk);
	skb_queue_tail(queue, skb);
	if (!sock_flag(sk, SOCK_DEAD))
		sk->sk_data_ready(sk);
	return NET_RX_SUCCESS;
}