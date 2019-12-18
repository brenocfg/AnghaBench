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
struct tcf_block {scalar_t__ keep_dst; } ;
struct Qdisc {int dummy; } ;
typedef  enum flow_block_binder_type { ____Placeholder_flow_block_binder_type } flow_block_binder_type ;

/* Variables and functions */
 int FLOW_BLOCK_BINDER_TYPE_CLSACT_EGRESS ; 
 int FLOW_BLOCK_BINDER_TYPE_CLSACT_INGRESS ; 
 int /*<<< orphan*/  netif_keep_dst (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qdisc_dev (struct Qdisc*) ; 

__attribute__((used)) static void
tcf_block_owner_netif_keep_dst(struct tcf_block *block,
			       struct Qdisc *q,
			       enum flow_block_binder_type binder_type)
{
	if (block->keep_dst &&
	    binder_type != FLOW_BLOCK_BINDER_TYPE_CLSACT_INGRESS &&
	    binder_type != FLOW_BLOCK_BINDER_TYPE_CLSACT_EGRESS)
		netif_keep_dst(qdisc_dev(q));
}