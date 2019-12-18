#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tcf_proto {TYPE_2__* chain; } ;
struct tcf_block {int dummy; } ;
struct tc_u_hnode {int /*<<< orphan*/  prio; int /*<<< orphan*/  handle; int /*<<< orphan*/  divisor; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  prio; int /*<<< orphan*/  handle; int /*<<< orphan*/  divisor; } ;
struct tc_cls_u32_offload {TYPE_1__ hnode; int /*<<< orphan*/  command; int /*<<< orphan*/  common; } ;
struct netlink_ext_ack {int dummy; } ;
struct TYPE_4__ {struct tcf_block* block; } ;

/* Variables and functions */
 int /*<<< orphan*/  TC_CLSU32_DELETE_HNODE ; 
 int /*<<< orphan*/  TC_SETUP_CLSU32 ; 
 int /*<<< orphan*/  tc_cls_common_offload_init (int /*<<< orphan*/ *,struct tcf_proto*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  tc_setup_cb_call (struct tcf_block*,int /*<<< orphan*/ ,struct tc_cls_u32_offload*,int,int) ; 

__attribute__((used)) static void u32_clear_hw_hnode(struct tcf_proto *tp, struct tc_u_hnode *h,
			       struct netlink_ext_ack *extack)
{
	struct tcf_block *block = tp->chain->block;
	struct tc_cls_u32_offload cls_u32 = {};

	tc_cls_common_offload_init(&cls_u32.common, tp, h->flags, extack);
	cls_u32.command = TC_CLSU32_DELETE_HNODE;
	cls_u32.hnode.divisor = h->divisor;
	cls_u32.hnode.handle = h->handle;
	cls_u32.hnode.prio = h->prio;

	tc_setup_cb_call(block, TC_SETUP_CLSU32, &cls_u32, false, true);
}