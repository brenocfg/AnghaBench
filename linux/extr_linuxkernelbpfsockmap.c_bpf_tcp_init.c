#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sock {scalar_t__ sk_family; TYPE_1__* sk_prot; } ;
struct smap_psock {int sk_proto; int /*<<< orphan*/  save_close; int /*<<< orphan*/  save_unhash; } ;
struct TYPE_7__ {int /*<<< orphan*/  close; int /*<<< orphan*/  unhash; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int EBUSY ; 
 int EINVAL ; 
 size_t SOCKMAP_IPV6 ; 
 int /*<<< orphan*/ * bpf_tcp_prots ; 
 int /*<<< orphan*/  build_protos (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 TYPE_1__* saved_tcpv6_prot ; 
 struct smap_psock* smap_psock_sk (struct sock*) ; 
 TYPE_1__* smp_load_acquire (TYPE_1__**) ; 
 int /*<<< orphan*/  smp_store_release (TYPE_1__**,TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcpv6_prot_lock ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  update_sk_prot (struct sock*,struct smap_psock*) ; 

__attribute__((used)) static int bpf_tcp_init(struct sock *sk)
{
	struct smap_psock *psock;

	rcu_read_lock();
	psock = smap_psock_sk(sk);
	if (unlikely(!psock)) {
		rcu_read_unlock();
		return -EINVAL;
	}

	if (unlikely(psock->sk_proto)) {
		rcu_read_unlock();
		return -EBUSY;
	}

	psock->save_unhash = sk->sk_prot->unhash;
	psock->save_close = sk->sk_prot->close;
	psock->sk_proto = sk->sk_prot;

	/* Build IPv6 sockmap whenever the address of tcpv6_prot changes */
	if (sk->sk_family == AF_INET6 &&
	    unlikely(sk->sk_prot != smp_load_acquire(&saved_tcpv6_prot))) {
		spin_lock_bh(&tcpv6_prot_lock);
		if (likely(sk->sk_prot != saved_tcpv6_prot)) {
			build_protos(bpf_tcp_prots[SOCKMAP_IPV6], sk->sk_prot);
			smp_store_release(&saved_tcpv6_prot, sk->sk_prot);
		}
		spin_unlock_bh(&tcpv6_prot_lock);
	}
	update_sk_prot(sk, psock);
	rcu_read_unlock();
	return 0;
}