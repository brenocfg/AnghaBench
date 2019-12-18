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
struct tcf_block_ext_info {int /*<<< orphan*/  binder_type; } ;
struct tcf_block {int dummy; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __tcf_block_put (struct tcf_block*,struct Qdisc*,struct tcf_block_ext_info*,int) ; 
 int /*<<< orphan*/  tcf_block_owner_del (struct tcf_block*,struct Qdisc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_chain0_head_change_cb_del (struct tcf_block*,struct tcf_block_ext_info*) ; 

void tcf_block_put_ext(struct tcf_block *block, struct Qdisc *q,
		       struct tcf_block_ext_info *ei)
{
	if (!block)
		return;
	tcf_chain0_head_change_cb_del(block, ei);
	tcf_block_owner_del(block, q, ei->binder_type);

	__tcf_block_put(block, q, ei, true);
}