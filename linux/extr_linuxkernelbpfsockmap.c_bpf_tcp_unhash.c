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
struct sock {TYPE_1__* sk_prot; } ;
struct smap_psock {void (* save_unhash ) (struct sock*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  (* unhash ) (struct sock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_tcp_remove (struct sock*,struct smap_psock*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct smap_psock* smap_psock_sk (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void bpf_tcp_unhash(struct sock *sk)
{
	void (*unhash_fun)(struct sock *sk);
	struct smap_psock *psock;

	rcu_read_lock();
	psock = smap_psock_sk(sk);
	if (unlikely(!psock)) {
		rcu_read_unlock();
		if (sk->sk_prot->unhash)
			sk->sk_prot->unhash(sk);
		return;
	}
	unhash_fun = psock->save_unhash;
	bpf_tcp_remove(sk, psock);
	rcu_read_unlock();
	unhash_fun(sk);
}