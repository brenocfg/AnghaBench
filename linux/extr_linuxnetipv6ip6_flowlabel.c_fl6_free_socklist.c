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
struct ipv6_pinfo {int /*<<< orphan*/  ipv6_fl_list; } ;
struct ipv6_fl_socklist {int /*<<< orphan*/  fl; int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int /*<<< orphan*/  fl_release (int /*<<< orphan*/ ) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 int /*<<< orphan*/  ip6_sk_fl_lock ; 
 int /*<<< orphan*/  kfree_rcu (struct ipv6_fl_socklist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  rcu_access_pointer (int /*<<< orphan*/ ) ; 
 struct ipv6_fl_socklist* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void fl6_free_socklist(struct sock *sk)
{
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct ipv6_fl_socklist *sfl;

	if (!rcu_access_pointer(np->ipv6_fl_list))
		return;

	spin_lock_bh(&ip6_sk_fl_lock);
	while ((sfl = rcu_dereference_protected(np->ipv6_fl_list,
						lockdep_is_held(&ip6_sk_fl_lock))) != NULL) {
		np->ipv6_fl_list = sfl->next;
		spin_unlock_bh(&ip6_sk_fl_lock);

		fl_release(sfl->fl);
		kfree_rcu(sfl, rcu);

		spin_lock_bh(&ip6_sk_fl_lock);
	}
	spin_unlock_bh(&ip6_sk_fl_lock);
}