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
struct sock {void* sk_state; int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;int /*<<< orphan*/  (* sk_data_ready ) (struct sock*) ;int /*<<< orphan*/  sk_receive_queue; int /*<<< orphan*/  sk_drops; } ;
struct sk_buff {int /*<<< orphan*/ * dev; } ;
struct pnpipehdr {int message_id; } ;
struct pep_sock {int /*<<< orphan*/  init_enable; int /*<<< orphan*/  rx_credits; int /*<<< orphan*/  rx_fc; } ;

/* Variables and functions */
 int NET_RX_DROP ; 
 int NET_RX_SUCCESS ; 
#define  PNS_PEP_CONNECT_RESP 133 
#define  PNS_PEP_DISCONNECT_RESP 132 
#define  PNS_PEP_ENABLE_RESP 131 
#define  PNS_PEP_STATUS_IND 130 
#define  PNS_PIPE_ALIGNED_DATA 129 
#define  PNS_PIPE_DATA 128 
 int /*<<< orphan*/  PN_PIPE_DISABLE ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 void* TCP_CLOSE_WAIT ; 
 void* TCP_ESTABLISHED ; 
 void* TCP_SYN_RECV ; 
 void* TCP_SYN_SENT ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pep_connresp_rcv (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  pep_enableresp_rcv (struct sock*,struct sk_buff*) ; 
 struct pep_sock* pep_sk (struct sock*) ; 
 int /*<<< orphan*/  pipe_rcv_status (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  pipe_start_flow_control (struct sock*) ; 
 int /*<<< orphan*/  pn_flow_safe (int /*<<< orphan*/ ) ; 
 struct pnpipehdr* pnp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_owner_r (struct sk_buff*,struct sock*) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int sock_queue_rcv_skb (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  stub2 (struct sock*) ; 

__attribute__((used)) static int pipe_handler_do_rcv(struct sock *sk, struct sk_buff *skb)
{
	struct pep_sock *pn = pep_sk(sk);
	struct pnpipehdr *hdr = pnp_hdr(skb);
	int err = NET_RX_SUCCESS;

	switch (hdr->message_id) {
	case PNS_PIPE_ALIGNED_DATA:
		__skb_pull(skb, 1);
		/* fall through */
	case PNS_PIPE_DATA:
		__skb_pull(skb, 3); /* Pipe data header */
		if (!pn_flow_safe(pn->rx_fc)) {
			err = sock_queue_rcv_skb(sk, skb);
			if (!err)
				return NET_RX_SUCCESS;
			err = NET_RX_DROP;
			break;
		}

		if (pn->rx_credits == 0) {
			atomic_inc(&sk->sk_drops);
			err = NET_RX_DROP;
			break;
		}
		pn->rx_credits--;
		skb->dev = NULL;
		skb_set_owner_r(skb, sk);
		skb_queue_tail(&sk->sk_receive_queue, skb);
		if (!sock_flag(sk, SOCK_DEAD))
			sk->sk_data_ready(sk);
		return NET_RX_SUCCESS;

	case PNS_PEP_CONNECT_RESP:
		if (sk->sk_state != TCP_SYN_SENT)
			break;
		if (!sock_flag(sk, SOCK_DEAD))
			sk->sk_state_change(sk);
		if (pep_connresp_rcv(sk, skb)) {
			sk->sk_state = TCP_CLOSE_WAIT;
			break;
		}
		if (pn->init_enable == PN_PIPE_DISABLE)
			sk->sk_state = TCP_SYN_RECV;
		else {
			sk->sk_state = TCP_ESTABLISHED;
			pipe_start_flow_control(sk);
		}
		break;

	case PNS_PEP_ENABLE_RESP:
		if (sk->sk_state != TCP_SYN_SENT)
			break;

		if (pep_enableresp_rcv(sk, skb)) {
			sk->sk_state = TCP_CLOSE_WAIT;
			break;
		}

		sk->sk_state = TCP_ESTABLISHED;
		pipe_start_flow_control(sk);
		break;

	case PNS_PEP_DISCONNECT_RESP:
		/* sock should already be dead, nothing to do */
		break;

	case PNS_PEP_STATUS_IND:
		pipe_rcv_status(sk, skb);
		break;
	}
	kfree_skb(skb);
	return err;
}