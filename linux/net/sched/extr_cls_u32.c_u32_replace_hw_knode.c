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
typedef  int /*<<< orphan*/  u32 ;
struct tcf_proto {TYPE_1__* chain; } ;
struct tcf_block {int dummy; } ;
struct tc_u_knode {int flags; int /*<<< orphan*/  in_hw_count; scalar_t__ ht_down; int /*<<< orphan*/  exts; int /*<<< orphan*/  res; int /*<<< orphan*/  sel; scalar_t__ mask; scalar_t__ val; int /*<<< orphan*/  fshift; int /*<<< orphan*/  handle; } ;
struct tc_u_hnode {int /*<<< orphan*/  handle; } ;
struct TYPE_4__ {int /*<<< orphan*/  link_handle; int /*<<< orphan*/ * exts; int /*<<< orphan*/ * res; int /*<<< orphan*/ * sel; scalar_t__ mask; scalar_t__ val; int /*<<< orphan*/  fshift; int /*<<< orphan*/  handle; } ;
struct tc_cls_u32_offload {TYPE_2__ knode; int /*<<< orphan*/  command; int /*<<< orphan*/  common; } ;
struct netlink_ext_ack {int dummy; } ;
struct TYPE_3__ {struct tcf_block* block; } ;

/* Variables and functions */
 int EINVAL ; 
 int TCA_CLS_FLAGS_IN_HW ; 
 int /*<<< orphan*/  TC_CLSU32_REPLACE_KNODE ; 
 int /*<<< orphan*/  TC_SETUP_CLSU32 ; 
 struct tc_u_hnode* rtnl_dereference (scalar_t__) ; 
 int /*<<< orphan*/  tc_cls_common_offload_init (int /*<<< orphan*/ *,struct tcf_proto*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int tc_setup_cb_add (struct tcf_block*,struct tcf_proto*,int /*<<< orphan*/ ,struct tc_cls_u32_offload*,int,int*,int /*<<< orphan*/ *,int) ; 
 int tc_skip_sw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u32_remove_hw_knode (struct tcf_proto*,struct tc_u_knode*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int u32_replace_hw_knode(struct tcf_proto *tp, struct tc_u_knode *n,
				u32 flags, struct netlink_ext_ack *extack)
{
	struct tc_u_hnode *ht = rtnl_dereference(n->ht_down);
	struct tcf_block *block = tp->chain->block;
	struct tc_cls_u32_offload cls_u32 = {};
	bool skip_sw = tc_skip_sw(flags);
	int err;

	tc_cls_common_offload_init(&cls_u32.common, tp, flags, extack);
	cls_u32.command = TC_CLSU32_REPLACE_KNODE;
	cls_u32.knode.handle = n->handle;
	cls_u32.knode.fshift = n->fshift;
#ifdef CONFIG_CLS_U32_MARK
	cls_u32.knode.val = n->val;
	cls_u32.knode.mask = n->mask;
#else
	cls_u32.knode.val = 0;
	cls_u32.knode.mask = 0;
#endif
	cls_u32.knode.sel = &n->sel;
	cls_u32.knode.res = &n->res;
	cls_u32.knode.exts = &n->exts;
	if (n->ht_down)
		cls_u32.knode.link_handle = ht->handle;

	err = tc_setup_cb_add(block, tp, TC_SETUP_CLSU32, &cls_u32, skip_sw,
			      &n->flags, &n->in_hw_count, true);
	if (err) {
		u32_remove_hw_knode(tp, n, NULL);
		return err;
	}

	if (skip_sw && !(n->flags & TCA_CLS_FLAGS_IN_HW))
		return -EINVAL;

	return 0;
}