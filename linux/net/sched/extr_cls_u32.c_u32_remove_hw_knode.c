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
struct tc_u_knode {int /*<<< orphan*/  in_hw_count; int /*<<< orphan*/  flags; int /*<<< orphan*/  handle; } ;
struct TYPE_3__ {int /*<<< orphan*/  handle; } ;
struct tc_cls_u32_offload {TYPE_1__ knode; int /*<<< orphan*/  command; int /*<<< orphan*/  common; } ;
struct netlink_ext_ack {int dummy; } ;
struct TYPE_4__ {struct tcf_block* block; } ;

/* Variables and functions */
 int /*<<< orphan*/  TC_CLSU32_DELETE_KNODE ; 
 int /*<<< orphan*/  TC_SETUP_CLSU32 ; 
 int /*<<< orphan*/  tc_cls_common_offload_init (int /*<<< orphan*/ *,struct tcf_proto*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  tc_setup_cb_destroy (struct tcf_block*,struct tcf_proto*,int /*<<< orphan*/ ,struct tc_cls_u32_offload*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void u32_remove_hw_knode(struct tcf_proto *tp, struct tc_u_knode *n,
				struct netlink_ext_ack *extack)
{
	struct tcf_block *block = tp->chain->block;
	struct tc_cls_u32_offload cls_u32 = {};

	tc_cls_common_offload_init(&cls_u32.common, tp, n->flags, extack);
	cls_u32.command = TC_CLSU32_DELETE_KNODE;
	cls_u32.knode.handle = n->handle;

	tc_setup_cb_destroy(block, tp, TC_SETUP_CLSU32, &cls_u32, false,
			    &n->flags, &n->in_hw_count, true);
}