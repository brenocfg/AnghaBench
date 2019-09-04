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
typedef  scalar_t__ u8 ;
struct sockaddr_pn {int dummy; } ;
struct sock {int sk_state; int /*<<< orphan*/  (* sk_data_ready ) (struct sock*) ;int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff {int dummy; } ;
struct pnpipehdr {scalar_t__ pipe_handle; int message_id; } ;
struct pep_sock {int /*<<< orphan*/  hlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int NET_RX_SUCCESS ; 
#define  PNS_PEP_CONNECT_REQ 133 
#define  PNS_PEP_CTRL_REQ 132 
#define  PNS_PEP_DISABLE_REQ 131 
#define  PNS_PEP_DISCONNECT_REQ 130 
#define  PNS_PEP_ENABLE_REQ 129 
#define  PNS_PEP_RESET_REQ 128 
 int /*<<< orphan*/  PN_PIPE_ERR_PEP_IN_USE ; 
 scalar_t__ PN_PIPE_INVALID_HANDLE ; 
 int /*<<< orphan*/  PN_PIPE_NO_ERROR ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int TCPF_CLOSE ; 
 int TCPF_CLOSE_WAIT ; 
 int TCPF_LISTEN ; 
 int TCP_LISTEN ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pep_ctrlreq_error (struct sock*,struct sk_buff*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct sock* pep_find_pipe (int /*<<< orphan*/ *,struct sockaddr_pn*,scalar_t__) ; 
 int /*<<< orphan*/  pep_reject_conn (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pep_reply (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pep_sock* pep_sk (struct sock*) ; 
 int pipe_handler_do_rcv (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  pn_skb_get_dst_sockaddr (struct sk_buff*,struct sockaddr_pn*) ; 
 struct pnpipehdr* pnp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  sk_acceptq_added (struct sock*) ; 
 int /*<<< orphan*/  sk_acceptq_is_full (struct sock*) ; 
 int sk_receive_skb (struct sock*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_queue_head (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static int pep_do_rcv(struct sock *sk, struct sk_buff *skb)
{
	struct pep_sock *pn = pep_sk(sk);
	struct sock *sknode;
	struct pnpipehdr *hdr;
	struct sockaddr_pn dst;
	u8 pipe_handle;

	if (!pskb_may_pull(skb, sizeof(*hdr)))
		goto drop;

	hdr = pnp_hdr(skb);
	pipe_handle = hdr->pipe_handle;
	if (pipe_handle == PN_PIPE_INVALID_HANDLE)
		goto drop;

	pn_skb_get_dst_sockaddr(skb, &dst);

	/* Look for an existing pipe handle */
	sknode = pep_find_pipe(&pn->hlist, &dst, pipe_handle);
	if (sknode)
		return sk_receive_skb(sknode, skb, 1);

	switch (hdr->message_id) {
	case PNS_PEP_CONNECT_REQ:
		if (sk->sk_state != TCP_LISTEN || sk_acceptq_is_full(sk)) {
			pep_reject_conn(sk, skb, PN_PIPE_ERR_PEP_IN_USE,
					GFP_ATOMIC);
			break;
		}
		skb_queue_head(&sk->sk_receive_queue, skb);
		sk_acceptq_added(sk);
		if (!sock_flag(sk, SOCK_DEAD))
			sk->sk_data_ready(sk);
		return NET_RX_SUCCESS;

	case PNS_PEP_DISCONNECT_REQ:
		pep_reply(sk, skb, PN_PIPE_NO_ERROR, NULL, 0, GFP_ATOMIC);
		break;

	case PNS_PEP_CTRL_REQ:
		pep_ctrlreq_error(sk, skb, PN_PIPE_INVALID_HANDLE, GFP_ATOMIC);
		break;

	case PNS_PEP_RESET_REQ:
	case PNS_PEP_ENABLE_REQ:
	case PNS_PEP_DISABLE_REQ:
		/* invalid handle is not even allowed here! */
		break;

	default:
		if ((1 << sk->sk_state)
				& ~(TCPF_CLOSE|TCPF_LISTEN|TCPF_CLOSE_WAIT))
			/* actively connected socket */
			return pipe_handler_do_rcv(sk, skb);
	}
drop:
	kfree_skb(skb);
	return NET_RX_SUCCESS;
}