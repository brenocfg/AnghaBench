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
struct TYPE_2__ {int fib_has_custom_rules; scalar_t__ fib_rules_require_fldissect; int /*<<< orphan*/  fib_num_tclassid_users; } ;
struct net {TYPE_1__ ipv4; } ;
struct fib_rule {struct net* fr_net; } ;
struct fib4_rule {scalar_t__ tclassid; } ;

/* Variables and functions */
 scalar_t__ fib_rule_requires_fldissect (struct fib_rule*) ; 
 int fib_unmerge (struct net*) ; 

__attribute__((used)) static int fib4_rule_delete(struct fib_rule *rule)
{
	struct net *net = rule->fr_net;
	int err;

	/* split local/main if they are not already split */
	err = fib_unmerge(net);
	if (err)
		goto errout;

#ifdef CONFIG_IP_ROUTE_CLASSID
	if (((struct fib4_rule *)rule)->tclassid)
		net->ipv4.fib_num_tclassid_users--;
#endif
	net->ipv4.fib_has_custom_rules = true;

	if (net->ipv4.fib_rules_require_fldissect &&
	    fib_rule_requires_fldissect(rule))
		net->ipv4.fib_rules_require_fldissect--;
errout:
	return err;
}