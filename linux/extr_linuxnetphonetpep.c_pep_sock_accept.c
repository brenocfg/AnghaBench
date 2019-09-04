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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct sockaddr_pn {int dummy; } ;
struct sock {scalar_t__ sk_state; int /*<<< orphan*/  sk_destruct; int /*<<< orphan*/  sk_protocol; int /*<<< orphan*/  sk_backlog_rcv; int /*<<< orphan*/  sk_prot; } ;
struct sk_buff {int dummy; } ;
struct pnpipehdr {scalar_t__ pipe_handle; int state_after_connect; int other_pep_type; scalar_t__* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  resource; void* dobject; void* sobject; } ;
struct pep_sock {int peer_type; int /*<<< orphan*/  hlist; scalar_t__ aligned; scalar_t__ init_enable; int /*<<< orphan*/  tx_fc; int /*<<< orphan*/  rx_fc; scalar_t__ rx_credits; scalar_t__ ifindex; int /*<<< orphan*/  tx_credits; scalar_t__ pipe_handle; int /*<<< orphan*/  ctrlreq_queue; struct sock* listener; TYPE_1__ pn_sk; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 int EPROTO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  PF_PHONET ; 
 int /*<<< orphan*/  PN_LEGACY_FLOW_CONTROL ; 
#define  PN_PIPE_DISABLE 131 
#define  PN_PIPE_ENABLE 130 
 int /*<<< orphan*/  PN_PIPE_ERR_INVALID_PARAM ; 
 int /*<<< orphan*/  PN_PIPE_ERR_OVERLOAD ; 
 int /*<<< orphan*/  PN_PIPE_ERR_PEP_IN_USE ; 
#define  PN_PIPE_SB_ALIGNED_DATA 129 
#define  PN_PIPE_SB_CONNECT_REQ_PEP_SUB_TYPE 128 
 scalar_t__ TCP_LISTEN ; 
 scalar_t__ TCP_SYN_RECV ; 
 int /*<<< orphan*/  __sock_put (struct sock*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int pep_accept_conn (struct sock*,struct sk_buff*) ; 
 struct sock* pep_find_pipe (int /*<<< orphan*/ *,struct sockaddr_pn*,scalar_t__) ; 
 scalar_t__* pep_get_sb (struct sk_buff*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  pep_reject_conn (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pep_sock* pep_sk (struct sock*) ; 
 int /*<<< orphan*/  pipe_destruct ; 
 int /*<<< orphan*/  pipe_do_rcv ; 
 int /*<<< orphan*/  pn_skb_get_dst_sockaddr (struct sk_buff*,struct sockaddr_pn*) ; 
 int /*<<< orphan*/  pn_skb_get_src_sockaddr (struct sk_buff*,struct sockaddr_pn*) ; 
 void* pn_sockaddr_get_object (struct sockaddr_pn*) ; 
 int /*<<< orphan*/  pn_sockaddr_get_resource (struct sockaddr_pn*) ; 
 struct pnpipehdr* pnp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sk_acceptq_removed (struct sock*) ; 
 int /*<<< orphan*/  sk_add_node (struct sock*,int /*<<< orphan*/ *) ; 
 struct sock* sk_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_recv_datagram (struct sock*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  sock_init_data (int /*<<< orphan*/ *,struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 scalar_t__ unlikely (struct sock*) ; 

__attribute__((used)) static struct sock *pep_sock_accept(struct sock *sk, int flags, int *errp,
				    bool kern)
{
	struct pep_sock *pn = pep_sk(sk), *newpn;
	struct sock *newsk = NULL;
	struct sk_buff *skb;
	struct pnpipehdr *hdr;
	struct sockaddr_pn dst, src;
	int err;
	u16 peer_type;
	u8 pipe_handle, enabled, n_sb;
	u8 aligned = 0;

	skb = skb_recv_datagram(sk, 0, flags & O_NONBLOCK, errp);
	if (!skb)
		return NULL;

	lock_sock(sk);
	if (sk->sk_state != TCP_LISTEN) {
		err = -EINVAL;
		goto drop;
	}
	sk_acceptq_removed(sk);

	err = -EPROTO;
	if (!pskb_may_pull(skb, sizeof(*hdr) + 4))
		goto drop;

	hdr = pnp_hdr(skb);
	pipe_handle = hdr->pipe_handle;
	switch (hdr->state_after_connect) {
	case PN_PIPE_DISABLE:
		enabled = 0;
		break;
	case PN_PIPE_ENABLE:
		enabled = 1;
		break;
	default:
		pep_reject_conn(sk, skb, PN_PIPE_ERR_INVALID_PARAM,
				GFP_KERNEL);
		goto drop;
	}
	peer_type = hdr->other_pep_type << 8;

	/* Parse sub-blocks (options) */
	n_sb = hdr->data[3];
	while (n_sb > 0) {
		u8 type, buf[1], len = sizeof(buf);
		const u8 *data = pep_get_sb(skb, &type, &len, buf);

		if (data == NULL)
			goto drop;
		switch (type) {
		case PN_PIPE_SB_CONNECT_REQ_PEP_SUB_TYPE:
			if (len < 1)
				goto drop;
			peer_type = (peer_type & 0xff00) | data[0];
			break;
		case PN_PIPE_SB_ALIGNED_DATA:
			aligned = data[0] != 0;
			break;
		}
		n_sb--;
	}

	/* Check for duplicate pipe handle */
	newsk = pep_find_pipe(&pn->hlist, &dst, pipe_handle);
	if (unlikely(newsk)) {
		__sock_put(newsk);
		newsk = NULL;
		pep_reject_conn(sk, skb, PN_PIPE_ERR_PEP_IN_USE, GFP_KERNEL);
		goto drop;
	}

	/* Create a new to-be-accepted sock */
	newsk = sk_alloc(sock_net(sk), PF_PHONET, GFP_KERNEL, sk->sk_prot,
			 kern);
	if (!newsk) {
		pep_reject_conn(sk, skb, PN_PIPE_ERR_OVERLOAD, GFP_KERNEL);
		err = -ENOBUFS;
		goto drop;
	}

	sock_init_data(NULL, newsk);
	newsk->sk_state = TCP_SYN_RECV;
	newsk->sk_backlog_rcv = pipe_do_rcv;
	newsk->sk_protocol = sk->sk_protocol;
	newsk->sk_destruct = pipe_destruct;

	newpn = pep_sk(newsk);
	pn_skb_get_dst_sockaddr(skb, &dst);
	pn_skb_get_src_sockaddr(skb, &src);
	newpn->pn_sk.sobject = pn_sockaddr_get_object(&dst);
	newpn->pn_sk.dobject = pn_sockaddr_get_object(&src);
	newpn->pn_sk.resource = pn_sockaddr_get_resource(&dst);
	sock_hold(sk);
	newpn->listener = sk;
	skb_queue_head_init(&newpn->ctrlreq_queue);
	newpn->pipe_handle = pipe_handle;
	atomic_set(&newpn->tx_credits, 0);
	newpn->ifindex = 0;
	newpn->peer_type = peer_type;
	newpn->rx_credits = 0;
	newpn->rx_fc = newpn->tx_fc = PN_LEGACY_FLOW_CONTROL;
	newpn->init_enable = enabled;
	newpn->aligned = aligned;

	err = pep_accept_conn(newsk, skb);
	if (err) {
		sock_put(newsk);
		newsk = NULL;
		goto drop;
	}
	sk_add_node(newsk, &pn->hlist);
drop:
	release_sock(sk);
	kfree_skb(skb);
	*errp = err;
	return newsk;
}