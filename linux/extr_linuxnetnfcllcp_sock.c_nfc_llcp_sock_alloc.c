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
struct socket {int /*<<< orphan*/  state; } ;
struct sock {int sk_type; int /*<<< orphan*/  sk_destruct; int /*<<< orphan*/  sk_protocol; int /*<<< orphan*/  sk_state; } ;
struct nfc_llcp_sock {int remote_ready; int /*<<< orphan*/  accept_queue; int /*<<< orphan*/  tx_pending_queue; int /*<<< orphan*/  tx_queue; int /*<<< orphan*/  reserved_ssap; scalar_t__ recv_ack_n; scalar_t__ recv_n; scalar_t__ send_ack_n; scalar_t__ send_n; int /*<<< orphan*/  miux; scalar_t__ rw; int /*<<< orphan*/  dsap; scalar_t__ ssap; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LLCP_CLOSED ; 
 scalar_t__ LLCP_MAX_MIUX ; 
 scalar_t__ LLCP_MAX_RW ; 
 int /*<<< orphan*/  LLCP_SAP_MAX ; 
 int /*<<< orphan*/  LLCP_SAP_SDP ; 
 int /*<<< orphan*/  NFC_SOCKPROTO_LLCP ; 
 int /*<<< orphan*/  PF_NFC ; 
 int /*<<< orphan*/  SS_UNCONNECTED ; 
 int /*<<< orphan*/  cpu_to_be16 (scalar_t__) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  llcp_sock_destruct ; 
 int /*<<< orphan*/  llcp_sock_proto ; 
 struct nfc_llcp_sock* nfc_llcp_sock (struct sock*) ; 
 int /*<<< orphan*/  nfc_llcp_socket_remote_param_init (struct nfc_llcp_sock*) ; 
 struct sock* sk_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_init_data (struct socket*,struct sock*) ; 

struct sock *nfc_llcp_sock_alloc(struct socket *sock, int type, gfp_t gfp, int kern)
{
	struct sock *sk;
	struct nfc_llcp_sock *llcp_sock;

	sk = sk_alloc(&init_net, PF_NFC, gfp, &llcp_sock_proto, kern);
	if (!sk)
		return NULL;

	llcp_sock = nfc_llcp_sock(sk);

	sock_init_data(sock, sk);
	sk->sk_state = LLCP_CLOSED;
	sk->sk_protocol = NFC_SOCKPROTO_LLCP;
	sk->sk_type = type;
	sk->sk_destruct = llcp_sock_destruct;

	llcp_sock->ssap = 0;
	llcp_sock->dsap = LLCP_SAP_SDP;
	llcp_sock->rw = LLCP_MAX_RW + 1;
	llcp_sock->miux = cpu_to_be16(LLCP_MAX_MIUX + 1);
	llcp_sock->send_n = llcp_sock->send_ack_n = 0;
	llcp_sock->recv_n = llcp_sock->recv_ack_n = 0;
	llcp_sock->remote_ready = 1;
	llcp_sock->reserved_ssap = LLCP_SAP_MAX;
	nfc_llcp_socket_remote_param_init(llcp_sock);
	skb_queue_head_init(&llcp_sock->tx_queue);
	skb_queue_head_init(&llcp_sock->tx_pending_queue);
	INIT_LIST_HEAD(&llcp_sock->accept_queue);

	if (sock != NULL)
		sock->state = SS_UNCONNECTED;

	return sk;
}