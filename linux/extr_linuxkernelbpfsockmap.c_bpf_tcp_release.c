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
struct sock {int /*<<< orphan*/ * sk_prot; } ;
struct smap_psock {int /*<<< orphan*/ * sk_proto; int /*<<< orphan*/ * cork; int /*<<< orphan*/  sock; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_start_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct smap_psock* smap_psock_sk (struct sock*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void bpf_tcp_release(struct sock *sk)
{
	struct smap_psock *psock;

	rcu_read_lock();
	psock = smap_psock_sk(sk);
	if (unlikely(!psock))
		goto out;

	if (psock->cork) {
		free_start_sg(psock->sock, psock->cork, true);
		kfree(psock->cork);
		psock->cork = NULL;
	}

	if (psock->sk_proto) {
		sk->sk_prot = psock->sk_proto;
		psock->sk_proto = NULL;
	}
out:
	rcu_read_unlock();
}