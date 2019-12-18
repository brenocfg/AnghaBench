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
struct udp_table {int mask; unsigned short log; } ;
struct udp_hslot {int count; int /*<<< orphan*/  lock; int /*<<< orphan*/  head; } ;
struct sock {scalar_t__ sk_family; scalar_t__ sk_reuseport; TYPE_3__* sk_prot; } ;
struct net {int dummy; } ;
struct TYPE_8__ {unsigned short inet_num; } ;
struct TYPE_5__ {struct udp_table* udp_table; } ;
struct TYPE_7__ {TYPE_1__ h; } ;
struct TYPE_6__ {unsigned short udp_portaddr_hash; unsigned short udp_port_hash; int /*<<< orphan*/  udp_portaddr_node; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  CONFIG_IPV6 ; 
 int /*<<< orphan*/  DECLARE_BITMAP (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PORTS_PER_CHAIN ; 
 int /*<<< orphan*/  SOCK_RCU_FREE ; 
 int /*<<< orphan*/ * bitmap ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inet_get_local_port_range (struct net*,int*,int*) ; 
 int /*<<< orphan*/  inet_is_local_reserved_port (struct net*,unsigned short) ; 
 TYPE_4__* inet_sk (struct sock*) ; 
 unsigned int prandom_u32 () ; 
 int reciprocal_scale (unsigned int,int) ; 
 int /*<<< orphan*/  sk_add_node_rcu (struct sock*,int /*<<< orphan*/ *) ; 
 scalar_t__ sk_unhashed (struct sock*) ; 
 struct net* sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_prot_inuse_add (struct net*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (unsigned short,int /*<<< orphan*/ *) ; 
 struct udp_hslot* udp_hashslot (struct udp_table*,struct net*,unsigned short) ; 
 struct udp_hslot* udp_hashslot2 (struct udp_table*,unsigned int) ; 
 scalar_t__ udp_lib_lport_inuse (struct net*,unsigned short,struct udp_hslot*,int /*<<< orphan*/ *,struct sock*,unsigned short) ; 
 int udp_lib_lport_inuse2 (struct net*,unsigned short,struct udp_hslot*,struct sock*) ; 
 scalar_t__ udp_reuseport_add_sock (struct sock*,struct udp_hslot*) ; 
 TYPE_2__* udp_sk (struct sock*) ; 

int udp_lib_get_port(struct sock *sk, unsigned short snum,
		     unsigned int hash2_nulladdr)
{
	struct udp_hslot *hslot, *hslot2;
	struct udp_table *udptable = sk->sk_prot->h.udp_table;
	int    error = 1;
	struct net *net = sock_net(sk);

	if (!snum) {
		int low, high, remaining;
		unsigned int rand;
		unsigned short first, last;
		DECLARE_BITMAP(bitmap, PORTS_PER_CHAIN);

		inet_get_local_port_range(net, &low, &high);
		remaining = (high - low) + 1;

		rand = prandom_u32();
		first = reciprocal_scale(rand, remaining) + low;
		/*
		 * force rand to be an odd multiple of UDP_HTABLE_SIZE
		 */
		rand = (rand | 1) * (udptable->mask + 1);
		last = first + udptable->mask + 1;
		do {
			hslot = udp_hashslot(udptable, net, first);
			bitmap_zero(bitmap, PORTS_PER_CHAIN);
			spin_lock_bh(&hslot->lock);
			udp_lib_lport_inuse(net, snum, hslot, bitmap, sk,
					    udptable->log);

			snum = first;
			/*
			 * Iterate on all possible values of snum for this hash.
			 * Using steps of an odd multiple of UDP_HTABLE_SIZE
			 * give us randomization and full range coverage.
			 */
			do {
				if (low <= snum && snum <= high &&
				    !test_bit(snum >> udptable->log, bitmap) &&
				    !inet_is_local_reserved_port(net, snum))
					goto found;
				snum += rand;
			} while (snum != first);
			spin_unlock_bh(&hslot->lock);
			cond_resched();
		} while (++first != last);
		goto fail;
	} else {
		hslot = udp_hashslot(udptable, net, snum);
		spin_lock_bh(&hslot->lock);
		if (hslot->count > 10) {
			int exist;
			unsigned int slot2 = udp_sk(sk)->udp_portaddr_hash ^ snum;

			slot2          &= udptable->mask;
			hash2_nulladdr &= udptable->mask;

			hslot2 = udp_hashslot2(udptable, slot2);
			if (hslot->count < hslot2->count)
				goto scan_primary_hash;

			exist = udp_lib_lport_inuse2(net, snum, hslot2, sk);
			if (!exist && (hash2_nulladdr != slot2)) {
				hslot2 = udp_hashslot2(udptable, hash2_nulladdr);
				exist = udp_lib_lport_inuse2(net, snum, hslot2,
							     sk);
			}
			if (exist)
				goto fail_unlock;
			else
				goto found;
		}
scan_primary_hash:
		if (udp_lib_lport_inuse(net, snum, hslot, NULL, sk, 0))
			goto fail_unlock;
	}
found:
	inet_sk(sk)->inet_num = snum;
	udp_sk(sk)->udp_port_hash = snum;
	udp_sk(sk)->udp_portaddr_hash ^= snum;
	if (sk_unhashed(sk)) {
		if (sk->sk_reuseport &&
		    udp_reuseport_add_sock(sk, hslot)) {
			inet_sk(sk)->inet_num = 0;
			udp_sk(sk)->udp_port_hash = 0;
			udp_sk(sk)->udp_portaddr_hash ^= snum;
			goto fail_unlock;
		}

		sk_add_node_rcu(sk, &hslot->head);
		hslot->count++;
		sock_prot_inuse_add(sock_net(sk), sk->sk_prot, 1);

		hslot2 = udp_hashslot2(udptable, udp_sk(sk)->udp_portaddr_hash);
		spin_lock(&hslot2->lock);
		if (IS_ENABLED(CONFIG_IPV6) && sk->sk_reuseport &&
		    sk->sk_family == AF_INET6)
			hlist_add_tail_rcu(&udp_sk(sk)->udp_portaddr_node,
					   &hslot2->head);
		else
			hlist_add_head_rcu(&udp_sk(sk)->udp_portaddr_node,
					   &hslot2->head);
		hslot2->count++;
		spin_unlock(&hslot2->lock);
	}
	sock_set_flag(sk, SOCK_RCU_FREE);
	error = 0;
fail_unlock:
	spin_unlock_bh(&hslot->lock);
fail:
	return error;
}