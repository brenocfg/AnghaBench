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
struct fib_rules_ops {unsigned int fib_rules_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 struct fib_rules_ops* lookup_rules_ops (struct net*,int) ; 
 int /*<<< orphan*/  rules_ops_put (struct fib_rules_ops*) ; 

unsigned int fib_rules_seq_read(struct net *net, int family)
{
	unsigned int fib_rules_seq;
	struct fib_rules_ops *ops;

	ASSERT_RTNL();

	ops = lookup_rules_ops(net, family);
	if (!ops)
		return 0;
	fib_rules_seq = ops->fib_rules_seq;
	rules_ops_put(ops);

	return fib_rules_seq;
}