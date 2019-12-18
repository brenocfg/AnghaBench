#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  union tpacket_req_u {int dummy; } tpacket_req_u ;
struct socket {struct sock* sk; } ;
struct sock {int /*<<< orphan*/  sk_receive_queue; int /*<<< orphan*/  sk_prot; } ;
struct TYPE_8__ {scalar_t__ pg_vec; } ;
struct TYPE_7__ {scalar_t__ pg_vec; } ;
struct TYPE_6__ {int /*<<< orphan*/ * dev; } ;
struct packet_sock {struct packet_fanout* rollover; TYPE_4__ tx_ring; TYPE_3__ rx_ring; int /*<<< orphan*/  bind_lock; TYPE_2__ prot_hook; } ;
struct packet_fanout {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  sklist_lock; } ;
struct net {TYPE_1__ packet; } ;
typedef  int /*<<< orphan*/  req_u ;

/* Variables and functions */
 int /*<<< orphan*/  dev_put (int /*<<< orphan*/ *) ; 
 struct packet_fanout* fanout_release (struct sock*) ; 
 int /*<<< orphan*/  fanout_release_data (struct packet_fanout*) ; 
 int /*<<< orphan*/  kfree (struct packet_fanout*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  memset (union tpacket_req_u*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  packet_cached_dev_reset (struct packet_sock*) ; 
 int /*<<< orphan*/  packet_flush_mclist (struct sock*) ; 
 int /*<<< orphan*/  packet_free_pending (struct packet_sock*) ; 
 int /*<<< orphan*/  packet_set_ring (struct sock*,union tpacket_req_u*,int,int) ; 
 struct packet_sock* pkt_sk (struct sock*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sk_del_node_init_rcu (struct sock*) ; 
 int /*<<< orphan*/  sk_refcnt_debug_release (struct sock*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 struct net* sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_orphan (struct sock*) ; 
 int /*<<< orphan*/  sock_prot_inuse_add (struct net*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_net () ; 
 int /*<<< orphan*/  unregister_prot_hook (struct sock*,int) ; 

__attribute__((used)) static int packet_release(struct socket *sock)
{
	struct sock *sk = sock->sk;
	struct packet_sock *po;
	struct packet_fanout *f;
	struct net *net;
	union tpacket_req_u req_u;

	if (!sk)
		return 0;

	net = sock_net(sk);
	po = pkt_sk(sk);

	mutex_lock(&net->packet.sklist_lock);
	sk_del_node_init_rcu(sk);
	mutex_unlock(&net->packet.sklist_lock);

	preempt_disable();
	sock_prot_inuse_add(net, sk->sk_prot, -1);
	preempt_enable();

	spin_lock(&po->bind_lock);
	unregister_prot_hook(sk, false);
	packet_cached_dev_reset(po);

	if (po->prot_hook.dev) {
		dev_put(po->prot_hook.dev);
		po->prot_hook.dev = NULL;
	}
	spin_unlock(&po->bind_lock);

	packet_flush_mclist(sk);

	lock_sock(sk);
	if (po->rx_ring.pg_vec) {
		memset(&req_u, 0, sizeof(req_u));
		packet_set_ring(sk, &req_u, 1, 0);
	}

	if (po->tx_ring.pg_vec) {
		memset(&req_u, 0, sizeof(req_u));
		packet_set_ring(sk, &req_u, 1, 1);
	}
	release_sock(sk);

	f = fanout_release(sk);

	synchronize_net();

	kfree(po->rollover);
	if (f) {
		fanout_release_data(f);
		kfree(f);
	}
	/*
	 *	Now the socket is dead. No more input will appear.
	 */
	sock_orphan(sk);
	sock->sk = NULL;

	/* Purge queues */

	skb_queue_purge(&sk->sk_receive_queue);
	packet_free_pending(po);
	sk_refcnt_debug_release(sk);

	sock_put(sk);
	return 0;
}