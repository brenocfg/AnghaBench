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
struct notifier_block {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int family; } ;
struct fib_rule_notifier_info {TYPE_1__ info; struct fib_rule* rule; } ;
struct fib_rule {int dummy; } ;
typedef  enum fib_event_type { ____Placeholder_fib_event_type } fib_event_type ;

/* Variables and functions */
 int call_fib_notifier (struct notifier_block*,struct net*,int,TYPE_1__*) ; 

__attribute__((used)) static int call_fib_rule_notifier(struct notifier_block *nb, struct net *net,
				  enum fib_event_type event_type,
				  struct fib_rule *rule, int family)
{
	struct fib_rule_notifier_info info = {
		.info.family = family,
		.rule = rule,
	};

	return call_fib_notifier(nb, net, event_type, &info.info);
}