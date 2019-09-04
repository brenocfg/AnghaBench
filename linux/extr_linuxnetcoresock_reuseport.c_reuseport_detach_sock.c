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
struct sock_reuseport {int num_socks; int /*<<< orphan*/  rcu; struct sock** socks; scalar_t__ reuseport_id; } ;
struct sock {int /*<<< orphan*/  sk_reuseport_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_sk_reuseport_detach (struct sock*) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sock_reuseport* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reuseport_free_rcu ; 
 int /*<<< orphan*/  reuseport_lock ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void reuseport_detach_sock(struct sock *sk)
{
	struct sock_reuseport *reuse;
	int i;

	spin_lock_bh(&reuseport_lock);
	reuse = rcu_dereference_protected(sk->sk_reuseport_cb,
					  lockdep_is_held(&reuseport_lock));

	/* At least one of the sk in this reuseport group is added to
	 * a bpf map.  Notify the bpf side.  The bpf map logic will
	 * remove the sk if it is indeed added to a bpf map.
	 */
	if (reuse->reuseport_id)
		bpf_sk_reuseport_detach(sk);

	rcu_assign_pointer(sk->sk_reuseport_cb, NULL);

	for (i = 0; i < reuse->num_socks; i++) {
		if (reuse->socks[i] == sk) {
			reuse->socks[i] = reuse->socks[reuse->num_socks - 1];
			reuse->num_socks--;
			if (reuse->num_socks == 0)
				call_rcu(&reuse->rcu, reuseport_free_rcu);
			break;
		}
	}
	spin_unlock_bh(&reuseport_lock);
}