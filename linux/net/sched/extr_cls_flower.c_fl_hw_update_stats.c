#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tcf_proto {TYPE_3__* chain; } ;
struct tcf_block {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  lastused; int /*<<< orphan*/  pkts; int /*<<< orphan*/  bytes; } ;
struct flow_cls_offload {unsigned long cookie; TYPE_2__ stats; int /*<<< orphan*/  classid; int /*<<< orphan*/  command; int /*<<< orphan*/  common; } ;
struct TYPE_4__ {int /*<<< orphan*/  classid; } ;
struct cls_fl_filter {int /*<<< orphan*/  exts; TYPE_1__ res; int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {struct tcf_block* block; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLOW_CLS_STATS ; 
 int /*<<< orphan*/  TC_SETUP_CLSFLOWER ; 
 int /*<<< orphan*/  tc_cls_common_offload_init (int /*<<< orphan*/ *,struct tcf_proto*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tc_setup_cb_call (struct tcf_block*,int /*<<< orphan*/ ,struct flow_cls_offload*,int,int) ; 
 int /*<<< orphan*/  tcf_exts_stats_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fl_hw_update_stats(struct tcf_proto *tp, struct cls_fl_filter *f,
			       bool rtnl_held)
{
	struct tcf_block *block = tp->chain->block;
	struct flow_cls_offload cls_flower = {};

	tc_cls_common_offload_init(&cls_flower.common, tp, f->flags, NULL);
	cls_flower.command = FLOW_CLS_STATS;
	cls_flower.cookie = (unsigned long) f;
	cls_flower.classid = f->res.classid;

	tc_setup_cb_call(block, TC_SETUP_CLSFLOWER, &cls_flower, false,
			 rtnl_held);

	tcf_exts_stats_update(&f->exts, cls_flower.stats.bytes,
			      cls_flower.stats.pkts,
			      cls_flower.stats.lastused);
}