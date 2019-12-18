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
struct vsock_sock {int rejected; int sent_request; int ignore_connecting_rst; int /*<<< orphan*/  connect_timeout; int /*<<< orphan*/  owner; int /*<<< orphan*/  trusted; int /*<<< orphan*/  pending_work; int /*<<< orphan*/  connect_work; scalar_t__ peer_shutdown; int /*<<< orphan*/  accept_queue; int /*<<< orphan*/  pending_links; int /*<<< orphan*/ * listener; int /*<<< orphan*/  connected_table; int /*<<< orphan*/  bound_table; int /*<<< orphan*/  remote_addr; int /*<<< orphan*/  local_addr; } ;
struct socket {int dummy; } ;
struct sock {unsigned short sk_type; int /*<<< orphan*/  sk_backlog_rcv; int /*<<< orphan*/  sk_destruct; } ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {scalar_t__ (* init ) (struct vsock_sock*,struct vsock_sock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AF_VSOCK ; 
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOCK_DONE ; 
 int /*<<< orphan*/  VMADDR_CID_ANY ; 
 int /*<<< orphan*/  VMADDR_PORT_ANY ; 
 int /*<<< orphan*/  VSOCK_DEFAULT_CONNECT_TIMEOUT ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_cred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_current_cred () ; 
 struct sock* sk_alloc (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sk_free (struct sock*) ; 
 int /*<<< orphan*/  sock_init_data (struct socket*,struct sock*) ; 
 int /*<<< orphan*/  sock_reset_flag (struct sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct vsock_sock*,struct vsock_sock*) ; 
 TYPE_1__* transport ; 
 int /*<<< orphan*/  vsock_addr_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsock_connect_timeout ; 
 int /*<<< orphan*/  vsock_insert_unbound (struct vsock_sock*) ; 
 int /*<<< orphan*/  vsock_pending_work ; 
 int /*<<< orphan*/  vsock_proto ; 
 int /*<<< orphan*/  vsock_queue_rcv_skb ; 
 struct vsock_sock* vsock_sk (struct sock*) ; 
 int /*<<< orphan*/  vsock_sk_destruct ; 

struct sock *__vsock_create(struct net *net,
			    struct socket *sock,
			    struct sock *parent,
			    gfp_t priority,
			    unsigned short type,
			    int kern)
{
	struct sock *sk;
	struct vsock_sock *psk;
	struct vsock_sock *vsk;

	sk = sk_alloc(net, AF_VSOCK, priority, &vsock_proto, kern);
	if (!sk)
		return NULL;

	sock_init_data(sock, sk);

	/* sk->sk_type is normally set in sock_init_data, but only if sock is
	 * non-NULL. We make sure that our sockets always have a type by
	 * setting it here if needed.
	 */
	if (!sock)
		sk->sk_type = type;

	vsk = vsock_sk(sk);
	vsock_addr_init(&vsk->local_addr, VMADDR_CID_ANY, VMADDR_PORT_ANY);
	vsock_addr_init(&vsk->remote_addr, VMADDR_CID_ANY, VMADDR_PORT_ANY);

	sk->sk_destruct = vsock_sk_destruct;
	sk->sk_backlog_rcv = vsock_queue_rcv_skb;
	sock_reset_flag(sk, SOCK_DONE);

	INIT_LIST_HEAD(&vsk->bound_table);
	INIT_LIST_HEAD(&vsk->connected_table);
	vsk->listener = NULL;
	INIT_LIST_HEAD(&vsk->pending_links);
	INIT_LIST_HEAD(&vsk->accept_queue);
	vsk->rejected = false;
	vsk->sent_request = false;
	vsk->ignore_connecting_rst = false;
	vsk->peer_shutdown = 0;
	INIT_DELAYED_WORK(&vsk->connect_work, vsock_connect_timeout);
	INIT_DELAYED_WORK(&vsk->pending_work, vsock_pending_work);

	psk = parent ? vsock_sk(parent) : NULL;
	if (parent) {
		vsk->trusted = psk->trusted;
		vsk->owner = get_cred(psk->owner);
		vsk->connect_timeout = psk->connect_timeout;
	} else {
		vsk->trusted = capable(CAP_NET_ADMIN);
		vsk->owner = get_current_cred();
		vsk->connect_timeout = VSOCK_DEFAULT_CONNECT_TIMEOUT;
	}

	if (transport->init(vsk, psk) < 0) {
		sk_free(sk);
		return NULL;
	}

	if (sock)
		vsock_insert_unbound(vsk);

	return sk;
}