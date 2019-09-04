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
struct smap_psock {void (* save_close ) (struct sock*,long) ;} ;
struct TYPE_2__ {void (* close ) (struct sock*,long) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_tcp_remove (struct sock*,struct smap_psock*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 struct smap_psock* smap_psock_sk (struct sock*) ; 
 void stub1 (struct sock*,long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void bpf_tcp_close(struct sock *sk, long timeout)
{
	void (*close_fun)(struct sock *sk, long timeout);
	struct smap_psock *psock;

	lock_sock(sk);
	rcu_read_lock();
	psock = smap_psock_sk(sk);
	if (unlikely(!psock)) {
		rcu_read_unlock();
		release_sock(sk);
		return sk->sk_prot->close(sk, timeout);
	}
	close_fun = psock->save_close;
	bpf_tcp_remove(sk, psock);
	rcu_read_unlock();
	release_sock(sk);
	close_fun(sk, timeout);
}