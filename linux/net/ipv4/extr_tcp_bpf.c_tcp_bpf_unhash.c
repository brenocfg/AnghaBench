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
struct sk_psock {void (* saved_unhash ) (struct sock*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  (* unhash ) (struct sock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct sk_psock* sk_psock (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  tcp_bpf_remove (struct sock*,struct sk_psock*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void tcp_bpf_unhash(struct sock *sk)
{
	void (*saved_unhash)(struct sock *sk);
	struct sk_psock *psock;

	rcu_read_lock();
	psock = sk_psock(sk);
	if (unlikely(!psock)) {
		rcu_read_unlock();
		if (sk->sk_prot->unhash)
			sk->sk_prot->unhash(sk);
		return;
	}

	saved_unhash = psock->saved_unhash;
	tcp_bpf_remove(sk, psock);
	rcu_read_unlock();
	saved_unhash(sk);
}