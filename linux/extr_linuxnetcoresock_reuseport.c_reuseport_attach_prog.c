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
struct sock_reuseport {int /*<<< orphan*/  prog; } ;
struct sock {int /*<<< orphan*/  sk_reuseport_cb; scalar_t__ sk_reuseport; } ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct bpf_prog*) ; 
 void* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int reuseport_alloc (struct sock*,int) ; 
 int /*<<< orphan*/  reuseport_lock ; 
 int /*<<< orphan*/  sk_reuseport_prog_free (struct bpf_prog*) ; 
 scalar_t__ sk_unhashed (struct sock*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int reuseport_attach_prog(struct sock *sk, struct bpf_prog *prog)
{
	struct sock_reuseport *reuse;
	struct bpf_prog *old_prog;

	if (sk_unhashed(sk) && sk->sk_reuseport) {
		int err = reuseport_alloc(sk, false);

		if (err)
			return err;
	} else if (!rcu_access_pointer(sk->sk_reuseport_cb)) {
		/* The socket wasn't bound with SO_REUSEPORT */
		return -EINVAL;
	}

	spin_lock_bh(&reuseport_lock);
	reuse = rcu_dereference_protected(sk->sk_reuseport_cb,
					  lockdep_is_held(&reuseport_lock));
	old_prog = rcu_dereference_protected(reuse->prog,
					     lockdep_is_held(&reuseport_lock));
	rcu_assign_pointer(reuse->prog, prog);
	spin_unlock_bh(&reuseport_lock);

	sk_reuseport_prog_free(old_prog);
	return 0;
}