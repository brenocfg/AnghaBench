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
struct tc_root_qopt_offload {int ingress; int /*<<< orphan*/  handle; int /*<<< orphan*/  command; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct Qdisc {int flags; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int TCQ_F_INGRESS ; 
 int /*<<< orphan*/  TC_ROOT_GRAFT ; 
 int /*<<< orphan*/  TC_SETUP_ROOT_QDISC ; 
 int /*<<< orphan*/  qdisc_offload_graft_helper (struct net_device*,int /*<<< orphan*/ *,struct Qdisc*,struct Qdisc*,int /*<<< orphan*/ ,struct tc_root_qopt_offload*,struct netlink_ext_ack*) ; 

__attribute__((used)) static void qdisc_offload_graft_root(struct net_device *dev,
				     struct Qdisc *new, struct Qdisc *old,
				     struct netlink_ext_ack *extack)
{
	struct tc_root_qopt_offload graft_offload = {
		.command	= TC_ROOT_GRAFT,
		.handle		= new ? new->handle : 0,
		.ingress	= (new && new->flags & TCQ_F_INGRESS) ||
				  (old && old->flags & TCQ_F_INGRESS),
	};

	qdisc_offload_graft_helper(dev, NULL, new, old,
				   TC_SETUP_ROOT_QDISC, &graft_offload, extack);
}