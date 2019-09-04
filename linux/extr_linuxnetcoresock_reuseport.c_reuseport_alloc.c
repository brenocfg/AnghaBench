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
struct sock_reuseport {int bind_inany; int num_socks; struct sock** socks; } ;
struct sock {int /*<<< orphan*/  sk_reuseport_cb; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_SOCKS ; 
 struct sock_reuseport* __reuseport_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct sock_reuseport*) ; 
 struct sock_reuseport* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reuseport_lock ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int reuseport_alloc(struct sock *sk, bool bind_inany)
{
	struct sock_reuseport *reuse;

	/* bh lock used since this function call may precede hlist lock in
	 * soft irq of receive path or setsockopt from process context
	 */
	spin_lock_bh(&reuseport_lock);

	/* Allocation attempts can occur concurrently via the setsockopt path
	 * and the bind/hash path.  Nothing to do when we lose the race.
	 */
	reuse = rcu_dereference_protected(sk->sk_reuseport_cb,
					  lockdep_is_held(&reuseport_lock));
	if (reuse) {
		/* Only set reuse->bind_inany if the bind_inany is true.
		 * Otherwise, it will overwrite the reuse->bind_inany
		 * which was set by the bind/hash path.
		 */
		if (bind_inany)
			reuse->bind_inany = bind_inany;
		goto out;
	}

	reuse = __reuseport_alloc(INIT_SOCKS);
	if (!reuse) {
		spin_unlock_bh(&reuseport_lock);
		return -ENOMEM;
	}

	reuse->socks[0] = sk;
	reuse->num_socks = 1;
	reuse->bind_inany = bind_inany;
	rcu_assign_pointer(sk->sk_reuseport_cb, reuse);

out:
	spin_unlock_bh(&reuseport_lock);

	return 0;
}