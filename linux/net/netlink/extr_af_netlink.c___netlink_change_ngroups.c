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
struct sock {size_t sk_protocol; } ;
struct netlink_table {unsigned int groups; int /*<<< orphan*/  listeners; } ;
struct listeners {int /*<<< orphan*/  masks; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ NLGRPSZ (unsigned int) ; 
 int /*<<< orphan*/  kfree_rcu (struct listeners*,int /*<<< orphan*/ ) ; 
 struct listeners* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct listeners* nl_deref_protected (int /*<<< orphan*/ ) ; 
 struct netlink_table* nl_table ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct listeners*) ; 

int __netlink_change_ngroups(struct sock *sk, unsigned int groups)
{
	struct listeners *new, *old;
	struct netlink_table *tbl = &nl_table[sk->sk_protocol];

	if (groups < 32)
		groups = 32;

	if (NLGRPSZ(tbl->groups) < NLGRPSZ(groups)) {
		new = kzalloc(sizeof(*new) + NLGRPSZ(groups), GFP_ATOMIC);
		if (!new)
			return -ENOMEM;
		old = nl_deref_protected(tbl->listeners);
		memcpy(new->masks, old->masks, NLGRPSZ(tbl->groups));
		rcu_assign_pointer(tbl->listeners, new);

		kfree_rcu(old, rcu);
	}
	tbl->groups = groups;

	return 0;
}