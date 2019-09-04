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
struct smap_psock {int /*<<< orphan*/  refcnt; } ;
struct sk_msg_buff {int flags; } ;

/* Variables and functions */
 int BPF_F_INGRESS ; 
 int bpf_tcp_ingress (struct sock*,int,struct smap_psock*,struct sk_msg_buff*,int) ; 
 int bpf_tcp_push (struct sock*,int,struct sk_msg_buff*,int,int) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  refcount_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 struct smap_psock* smap_psock_sk (struct sock*) ; 
 int /*<<< orphan*/  smap_release_sock (struct smap_psock*,struct sock*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int bpf_tcp_sendmsg_do_redirect(struct sock *sk, int send,
				       struct sk_msg_buff *md,
				       int flags)
{
	bool ingress = !!(md->flags & BPF_F_INGRESS);
	struct smap_psock *psock;
	int err = 0;

	rcu_read_lock();
	psock = smap_psock_sk(sk);
	if (unlikely(!psock))
		goto out_rcu;

	if (!refcount_inc_not_zero(&psock->refcnt))
		goto out_rcu;

	rcu_read_unlock();

	if (ingress) {
		err = bpf_tcp_ingress(sk, send, psock, md, flags);
	} else {
		lock_sock(sk);
		err = bpf_tcp_push(sk, send, md, flags, false);
		release_sock(sk);
	}
	smap_release_sock(psock, sk);
	return err;
out_rcu:
	rcu_read_unlock();
	return 0;
}