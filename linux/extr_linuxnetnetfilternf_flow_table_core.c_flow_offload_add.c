#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct nf_flowtable {int /*<<< orphan*/  rhashtable; } ;
struct flow_offload {TYPE_1__* tuplehash; scalar_t__ timeout; } ;
struct TYPE_2__ {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 size_t FLOW_OFFLOAD_DIR_ORIGINAL ; 
 size_t FLOW_OFFLOAD_DIR_REPLY ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  nf_flow_offload_rhash_params ; 
 int /*<<< orphan*/  rhashtable_insert_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int flow_offload_add(struct nf_flowtable *flow_table, struct flow_offload *flow)
{
	flow->timeout = (u32)jiffies;

	rhashtable_insert_fast(&flow_table->rhashtable,
			       &flow->tuplehash[FLOW_OFFLOAD_DIR_ORIGINAL].node,
			       nf_flow_offload_rhash_params);
	rhashtable_insert_fast(&flow_table->rhashtable,
			       &flow->tuplehash[FLOW_OFFLOAD_DIR_REPLY].node,
			       nf_flow_offload_rhash_params);
	return 0;
}