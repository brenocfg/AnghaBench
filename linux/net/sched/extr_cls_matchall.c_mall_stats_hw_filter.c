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
struct TYPE_3__ {int /*<<< orphan*/  lastused; int /*<<< orphan*/  pkts; int /*<<< orphan*/  bytes; } ;
struct tc_cls_matchall_offload {unsigned long cookie; TYPE_1__ stats; int /*<<< orphan*/  command; int /*<<< orphan*/  common; } ;
struct cls_mall_head {int /*<<< orphan*/  exts; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {struct tcf_block* block; } ;

/* Variables and functions */
 int /*<<< orphan*/  TC_CLSMATCHALL_STATS ; 
 int /*<<< orphan*/  TC_SETUP_CLSMATCHALL ; 
 int /*<<< orphan*/  tc_cls_common_offload_init (int /*<<< orphan*/ *,struct tcf_proto*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tc_setup_cb_call (struct tcf_block*,int /*<<< orphan*/ ,struct tc_cls_matchall_offload*,int,int) ; 
 int /*<<< orphan*/  tcf_exts_stats_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mall_stats_hw_filter(struct tcf_proto *tp,
				 struct cls_mall_head *head,
				 unsigned long cookie)
{
	struct tc_cls_matchall_offload cls_mall = {};
	struct tcf_block *block = tp->chain->block;

	tc_cls_common_offload_init(&cls_mall.common, tp, head->flags, NULL);
	cls_mall.command = TC_CLSMATCHALL_STATS;
	cls_mall.cookie = cookie;

	tc_setup_cb_call(block, TC_SETUP_CLSMATCHALL, &cls_mall, false, true);

	tcf_exts_stats_update(&head->exts, cls_mall.stats.bytes,
			      cls_mall.stats.pkts, cls_mall.stats.lastused);
}