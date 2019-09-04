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
struct sock_reuseport {int num_socks; int max_socks; int /*<<< orphan*/  rcu; struct sock** socks; } ;
struct sock {int /*<<< orphan*/  sk_reuseport_cb; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct sock_reuseport*) ; 
 struct sock_reuseport* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int reuseport_alloc (struct sock*,int) ; 
 int /*<<< orphan*/  reuseport_free_rcu ; 
 struct sock_reuseport* reuseport_grow (struct sock_reuseport*) ; 
 int /*<<< orphan*/  reuseport_lock ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int reuseport_add_sock(struct sock *sk, struct sock *sk2, bool bind_inany)
{
	struct sock_reuseport *old_reuse, *reuse;

	if (!rcu_access_pointer(sk2->sk_reuseport_cb)) {
		int err = reuseport_alloc(sk2, bind_inany);

		if (err)
			return err;
	}

	spin_lock_bh(&reuseport_lock);
	reuse = rcu_dereference_protected(sk2->sk_reuseport_cb,
					  lockdep_is_held(&reuseport_lock));
	old_reuse = rcu_dereference_protected(sk->sk_reuseport_cb,
					     lockdep_is_held(&reuseport_lock));
	if (old_reuse && old_reuse->num_socks != 1) {
		spin_unlock_bh(&reuseport_lock);
		return -EBUSY;
	}

	if (reuse->num_socks == reuse->max_socks) {
		reuse = reuseport_grow(reuse);
		if (!reuse) {
			spin_unlock_bh(&reuseport_lock);
			return -ENOMEM;
		}
	}

	reuse->socks[reuse->num_socks] = sk;
	/* paired with smp_rmb() in reuseport_select_sock() */
	smp_wmb();
	reuse->num_socks++;
	rcu_assign_pointer(sk->sk_reuseport_cb, reuse);

	spin_unlock_bh(&reuseport_lock);

	if (old_reuse)
		call_rcu(&old_reuse->rcu, reuseport_free_rcu);
	return 0;
}