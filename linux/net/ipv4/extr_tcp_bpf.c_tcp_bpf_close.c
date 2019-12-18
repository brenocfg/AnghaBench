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
struct sk_psock {void (* saved_close ) (struct sock*,long) ;} ;
struct TYPE_2__ {void (* close ) (struct sock*,long) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 struct sk_psock* sk_psock (struct sock*) ; 
 void stub1 (struct sock*,long) ; 
 int /*<<< orphan*/  tcp_bpf_remove (struct sock*,struct sk_psock*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void tcp_bpf_close(struct sock *sk, long timeout)
{
	void (*saved_close)(struct sock *sk, long timeout);
	struct sk_psock *psock;

	lock_sock(sk);
	rcu_read_lock();
	psock = sk_psock(sk);
	if (unlikely(!psock)) {
		rcu_read_unlock();
		release_sock(sk);
		return sk->sk_prot->close(sk, timeout);
	}

	saved_close = psock->saved_close;
	tcp_bpf_remove(sk, psock);
	rcu_read_unlock();
	release_sock(sk);
	saved_close(sk, timeout);
}