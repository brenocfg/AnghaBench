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
struct tcf_proto {TYPE_1__* ops; int /*<<< orphan*/  chain; } ;
struct netlink_ext_ack {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  owner; int /*<<< orphan*/  (* destroy ) (struct tcf_proto*,int,struct netlink_ext_ack*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_rcu (struct tcf_proto*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  stub1 (struct tcf_proto*,int,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  tcf_chain_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_proto_signal_destroyed (int /*<<< orphan*/ ,struct tcf_proto*) ; 

__attribute__((used)) static void tcf_proto_destroy(struct tcf_proto *tp, bool rtnl_held,
			      bool sig_destroy, struct netlink_ext_ack *extack)
{
	tp->ops->destroy(tp, rtnl_held, extack);
	if (sig_destroy)
		tcf_proto_signal_destroyed(tp->chain, tp);
	tcf_chain_put(tp->chain);
	module_put(tp->ops->owner);
	kfree_rcu(tp, rcu);
}