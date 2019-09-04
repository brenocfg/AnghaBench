#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct udp_table {int dummy; } ;
struct udp_hslot {int /*<<< orphan*/  lock; int /*<<< orphan*/  count; int /*<<< orphan*/  head; } ;
struct sock {int /*<<< orphan*/  sk_reuseport_cb; TYPE_2__* sk_prot; } ;
struct TYPE_6__ {int /*<<< orphan*/  udp_portaddr_node; int /*<<< orphan*/  udp_port_hash; int /*<<< orphan*/  udp_portaddr_hash; } ;
struct TYPE_4__ {struct udp_table* udp_table; } ;
struct TYPE_5__ {TYPE_1__ h; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_del_init_rcu (int /*<<< orphan*/ *) ; 
 scalar_t__ rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reuseport_detach_sock (struct sock*) ; 
 scalar_t__ sk_hashed (struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct udp_hslot* udp_hashslot (struct udp_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct udp_hslot* udp_hashslot2 (struct udp_table*,int /*<<< orphan*/ ) ; 
 TYPE_3__* udp_sk (struct sock*) ; 

void udp_lib_rehash(struct sock *sk, u16 newhash)
{
	if (sk_hashed(sk)) {
		struct udp_table *udptable = sk->sk_prot->h.udp_table;
		struct udp_hslot *hslot, *hslot2, *nhslot2;

		hslot2 = udp_hashslot2(udptable, udp_sk(sk)->udp_portaddr_hash);
		nhslot2 = udp_hashslot2(udptable, newhash);
		udp_sk(sk)->udp_portaddr_hash = newhash;

		if (hslot2 != nhslot2 ||
		    rcu_access_pointer(sk->sk_reuseport_cb)) {
			hslot = udp_hashslot(udptable, sock_net(sk),
					     udp_sk(sk)->udp_port_hash);
			/* we must lock primary chain too */
			spin_lock_bh(&hslot->lock);
			if (rcu_access_pointer(sk->sk_reuseport_cb))
				reuseport_detach_sock(sk);

			if (hslot2 != nhslot2) {
				spin_lock(&hslot2->lock);
				hlist_del_init_rcu(&udp_sk(sk)->udp_portaddr_node);
				hslot2->count--;
				spin_unlock(&hslot2->lock);

				spin_lock(&nhslot2->lock);
				hlist_add_head_rcu(&udp_sk(sk)->udp_portaddr_node,
							 &nhslot2->head);
				nhslot2->count++;
				spin_unlock(&nhslot2->lock);
			}

			spin_unlock_bh(&hslot->lock);
		}
	}
}