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
struct TYPE_2__ {int /*<<< orphan*/  fib_seq; } ;
struct net {TYPE_1__ ipv4; } ;
struct fib_notifier_info {int /*<<< orphan*/  family; } ;
typedef  enum fib_event_type { ____Placeholder_fib_event_type } fib_event_type ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int call_fib_notifiers (struct net*,int,struct fib_notifier_info*) ; 

int call_fib4_notifiers(struct net *net, enum fib_event_type event_type,
			struct fib_notifier_info *info)
{
	ASSERT_RTNL();

	info->family = AF_INET;
	net->ipv4.fib_seq++;
	return call_fib_notifiers(net, event_type, info);
}