#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  rules_ops; } ;
struct net {TYPE_1__ ipv4; } ;
struct flowi4 {int dummy; } ;
struct fib_result {int /*<<< orphan*/  tclassid; } ;
struct fib_lookup_arg {unsigned int flags; scalar_t__ rule; struct fib_result* result; } ;
struct fib4_rule {int /*<<< orphan*/  tclassid; } ;

/* Variables and functions */
 int ENETUNREACH ; 
 int ESRCH ; 
 int fib_rules_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fib_lookup_arg*) ; 
 int /*<<< orphan*/  flowi4_to_flowi (struct flowi4*) ; 
 int /*<<< orphan*/  l3mdev_update_flow (struct net*,int /*<<< orphan*/ ) ; 

int __fib_lookup(struct net *net, struct flowi4 *flp,
		 struct fib_result *res, unsigned int flags)
{
	struct fib_lookup_arg arg = {
		.result = res,
		.flags = flags,
	};
	int err;

	/* update flow if oif or iif point to device enslaved to l3mdev */
	l3mdev_update_flow(net, flowi4_to_flowi(flp));

	err = fib_rules_lookup(net->ipv4.rules_ops, flowi4_to_flowi(flp), 0, &arg);
#ifdef CONFIG_IP_ROUTE_CLASSID
	if (arg.rule)
		res->tclassid = ((struct fib4_rule *)arg.rule)->tclassid;
	else
		res->tclassid = 0;
#endif

	if (err == -ESRCH)
		err = -ENETUNREACH;

	return err;
}