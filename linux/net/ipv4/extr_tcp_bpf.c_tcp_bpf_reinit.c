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
struct sock {int dummy; } ;
struct sk_psock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct sk_psock* sk_psock (struct sock*) ; 
 int /*<<< orphan*/  sock_owned_by_me (struct sock*) ; 
 int /*<<< orphan*/  tcp_bpf_reinit_sk_prot (struct sock*,struct sk_psock*) ; 

void tcp_bpf_reinit(struct sock *sk)
{
	struct sk_psock *psock;

	sock_owned_by_me(sk);

	rcu_read_lock();
	psock = sk_psock(sk);
	tcp_bpf_reinit_sk_prot(sk, psock);
	rcu_read_unlock();
}