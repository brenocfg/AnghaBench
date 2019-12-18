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
struct lockd_net {int /*<<< orphan*/  lockd_manager; int /*<<< orphan*/  grace_period_end; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct net init_net ; 
 int /*<<< orphan*/  lockd_net_id ; 
 int /*<<< orphan*/  locks_end_grace (int /*<<< orphan*/ *) ; 
 struct lockd_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsvc_invalidate_all () ; 
 scalar_t__ nlmsvc_ops ; 
 int /*<<< orphan*/  set_grace_period (struct net*) ; 

__attribute__((used)) static void restart_grace(void)
{
	if (nlmsvc_ops) {
		struct net *net = &init_net;
		struct lockd_net *ln = net_generic(net, lockd_net_id);

		cancel_delayed_work_sync(&ln->grace_period_end);
		locks_end_grace(&ln->lockd_manager);
		nlmsvc_invalidate_all();
		set_grace_period(net);
	}
}