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
struct net {int dummy; } ;
struct ip6_flowlabel {int /*<<< orphan*/  users; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 struct ip6_flowlabel* __fl_lookup (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock_bh () ; 
 int /*<<< orphan*/  rcu_read_unlock_bh () ; 

__attribute__((used)) static struct ip6_flowlabel *fl_lookup(struct net *net, __be32 label)
{
	struct ip6_flowlabel *fl;

	rcu_read_lock_bh();
	fl = __fl_lookup(net, label);
	if (fl && !atomic_inc_not_zero(&fl->users))
		fl = NULL;
	rcu_read_unlock_bh();
	return fl;
}