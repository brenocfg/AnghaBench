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
struct netlink_ext_ack {int dummy; } ;
struct flow_cls_common_offload {int prio; struct netlink_ext_ack* extack; int /*<<< orphan*/  protocol; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */

__attribute__((used)) static void nft_flow_offload_common_init(struct flow_cls_common_offload *common,
					 __be16 proto, int priority,
					 struct netlink_ext_ack *extack)
{
	common->protocol = proto;
	common->prio = priority;
	common->extack = extack;
}