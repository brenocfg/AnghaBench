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
struct tcf_proto {TYPE_1__* chain; } ;
struct tcf_block {int dummy; } ;
struct tc_u_knode {int /*<<< orphan*/  in_hw_count; int /*<<< orphan*/  flags; scalar_t__ ht_down; int /*<<< orphan*/  exts; int /*<<< orphan*/  res; int /*<<< orphan*/  sel; scalar_t__ mask; scalar_t__ val; int /*<<< orphan*/  fshift; int /*<<< orphan*/  handle; } ;
struct tc_u_hnode {int /*<<< orphan*/  handle; } ;
struct TYPE_4__ {int /*<<< orphan*/  link_handle; int /*<<< orphan*/ * exts; int /*<<< orphan*/ * res; int /*<<< orphan*/ * sel; scalar_t__ mask; scalar_t__ val; int /*<<< orphan*/  fshift; int /*<<< orphan*/  handle; } ;
struct tc_cls_u32_offload {TYPE_2__ knode; int /*<<< orphan*/  command; int /*<<< orphan*/  common; } ;
struct netlink_ext_ack {int dummy; } ;
typedef  int /*<<< orphan*/  flow_setup_cb_t ;
struct TYPE_3__ {struct tcf_block* block; } ;

/* Variables and functions */
 int /*<<< orphan*/  TC_CLSU32_DELETE_KNODE ; 
 int /*<<< orphan*/  TC_CLSU32_REPLACE_KNODE ; 
 int /*<<< orphan*/  TC_SETUP_CLSU32 ; 
 struct tc_u_hnode* rtnl_dereference (scalar_t__) ; 
 int /*<<< orphan*/  tc_cls_common_offload_init (int /*<<< orphan*/ *,struct tcf_proto*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int tc_setup_cb_reoffload (struct tcf_block*,struct tcf_proto*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct tc_cls_u32_offload*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int u32_reoffload_knode(struct tcf_proto *tp, struct tc_u_knode *n,
			       bool add, flow_setup_cb_t *cb, void *cb_priv,
			       struct netlink_ext_ack *extack)
{
	struct tc_u_hnode *ht = rtnl_dereference(n->ht_down);
	struct tcf_block *block = tp->chain->block;
	struct tc_cls_u32_offload cls_u32 = {};
	int err;

	tc_cls_common_offload_init(&cls_u32.common, tp, n->flags, extack);
	cls_u32.command = add ?
		TC_CLSU32_REPLACE_KNODE : TC_CLSU32_DELETE_KNODE;
	cls_u32.knode.handle = n->handle;

	if (add) {
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
	}

	err = tc_setup_cb_reoffload(block, tp, add, cb, TC_SETUP_CLSU32,
				    &cls_u32, cb_priv, &n->flags,
				    &n->in_hw_count);
	if (err)
		return err;

	return 0;
}