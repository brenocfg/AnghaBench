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
struct fib_notifier_info {struct net* net; } ;
typedef  enum fib_event_type { ____Placeholder_fib_event_type } fib_event_type ;

/* Variables and functions */
 int atomic_notifier_call_chain (int /*<<< orphan*/ *,int,struct fib_notifier_info*) ; 
 int /*<<< orphan*/  fib_chain ; 
 int notifier_to_errno (int) ; 

int call_fib_notifiers(struct net *net, enum fib_event_type event_type,
		       struct fib_notifier_info *info)
{
	int err;

	info->net = net;
	err = atomic_notifier_call_chain(&fib_chain, event_type, info);
	return notifier_to_errno(err);
}