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
struct socket {int type; int /*<<< orphan*/ * ops; } ;
struct sock {int dummy; } ;
struct net {int dummy; } ;
struct kcm_net {int /*<<< orphan*/  mutex; int /*<<< orphan*/  count; int /*<<< orphan*/  mux_list; } ;
struct kcm_mux {int /*<<< orphan*/  rx_hold_queue; int /*<<< orphan*/  kcm_mux_list; struct kcm_net* knet; int /*<<< orphan*/  psocks_avail; int /*<<< orphan*/  psocks_ready; int /*<<< orphan*/  psocks; int /*<<< orphan*/  kcm_tx_waiters; int /*<<< orphan*/  kcm_rx_waiters; int /*<<< orphan*/  kcm_socks; int /*<<< orphan*/  rx_lock; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROTONOSUPPORT ; 
 int ESOCKTNOSUPPORT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int KCMPROTO_CONNECTED ; 
 int /*<<< orphan*/  PF_KCM ; 
#define  SOCK_DGRAM 129 
#define  SOCK_SEQPACKET 128 
 int /*<<< orphan*/  init_kcm_sock (int /*<<< orphan*/ ,struct kcm_mux*) ; 
 int /*<<< orphan*/  kcm_dgram_ops ; 
 int /*<<< orphan*/  kcm_muxp ; 
 int /*<<< orphan*/  kcm_net_id ; 
 int /*<<< orphan*/  kcm_proto ; 
 int /*<<< orphan*/  kcm_seqpacket_ops ; 
 int /*<<< orphan*/  kcm_sk (struct sock*) ; 
 struct kcm_mux* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct kcm_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 struct sock* sk_alloc (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sk_free (struct sock*) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_init_data (struct socket*,struct sock*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kcm_create(struct net *net, struct socket *sock,
		      int protocol, int kern)
{
	struct kcm_net *knet = net_generic(net, kcm_net_id);
	struct sock *sk;
	struct kcm_mux *mux;

	switch (sock->type) {
	case SOCK_DGRAM:
		sock->ops = &kcm_dgram_ops;
		break;
	case SOCK_SEQPACKET:
		sock->ops = &kcm_seqpacket_ops;
		break;
	default:
		return -ESOCKTNOSUPPORT;
	}

	if (protocol != KCMPROTO_CONNECTED)
		return -EPROTONOSUPPORT;

	sk = sk_alloc(net, PF_KCM, GFP_KERNEL, &kcm_proto, kern);
	if (!sk)
		return -ENOMEM;

	/* Allocate a kcm mux, shared between KCM sockets */
	mux = kmem_cache_zalloc(kcm_muxp, GFP_KERNEL);
	if (!mux) {
		sk_free(sk);
		return -ENOMEM;
	}

	spin_lock_init(&mux->lock);
	spin_lock_init(&mux->rx_lock);
	INIT_LIST_HEAD(&mux->kcm_socks);
	INIT_LIST_HEAD(&mux->kcm_rx_waiters);
	INIT_LIST_HEAD(&mux->kcm_tx_waiters);

	INIT_LIST_HEAD(&mux->psocks);
	INIT_LIST_HEAD(&mux->psocks_ready);
	INIT_LIST_HEAD(&mux->psocks_avail);

	mux->knet = knet;

	/* Add new MUX to list */
	mutex_lock(&knet->mutex);
	list_add_rcu(&mux->kcm_mux_list, &knet->mux_list);
	knet->count++;
	mutex_unlock(&knet->mutex);

	skb_queue_head_init(&mux->rx_hold_queue);

	/* Init KCM socket */
	sock_init_data(sock, sk);
	init_kcm_sock(kcm_sk(sk), mux);

	return 0;
}