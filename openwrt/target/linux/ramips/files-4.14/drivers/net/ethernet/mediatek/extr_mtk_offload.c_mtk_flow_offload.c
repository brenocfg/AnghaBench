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
typedef  int u32 ;
struct TYPE_4__ {int time_stamp; int /*<<< orphan*/  psn; } ;
struct mtk_foe_entry {TYPE_2__ bfib1; } ;
struct mtk_eth {int /*<<< orphan*/ * foe_flow_table; } ;
struct flow_offload_tuple {scalar_t__ l4proto; int l3proto; } ;
struct flow_offload_hw_path {int /*<<< orphan*/  eth_dest; int /*<<< orphan*/  eth_src; } ;
struct flow_offload {TYPE_1__* tuplehash; } ;
typedef  enum flow_offload_type { ____Placeholder_flow_offload_type } flow_offload_type ;
struct TYPE_3__ {struct flow_offload_tuple tuple; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int EINVAL ; 
 int FLOW_OFFLOAD_DEL ; 
 size_t FLOW_OFFLOAD_DIR_ORIGINAL ; 
 size_t FLOW_OFFLOAD_DIR_REPLY ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 int /*<<< orphan*/  mtk_check_entry_available (struct mtk_eth*,int) ; 
 int mtk_flow_hash_v4 (struct flow_offload_tuple*) ; 
 int /*<<< orphan*/  mtk_foe_prepare_v4 (struct mtk_foe_entry*,struct flow_offload_tuple*,struct flow_offload_tuple*,struct flow_offload_hw_path*,struct flow_offload_hw_path*) ; 
 int /*<<< orphan*/  mtk_foe_set_mac (struct mtk_foe_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_foe_write (struct mtk_eth*,int,struct mtk_foe_entry*) ; 
 int mtk_r32 (struct mtk_eth*,int) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct flow_offload*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

int mtk_flow_offload(struct mtk_eth *eth,
		     enum flow_offload_type type,
		     struct flow_offload *flow,
		     struct flow_offload_hw_path *src,
		     struct flow_offload_hw_path *dest)
{
	struct flow_offload_tuple *otuple = &flow->tuplehash[FLOW_OFFLOAD_DIR_ORIGINAL].tuple;
	struct flow_offload_tuple *rtuple = &flow->tuplehash[FLOW_OFFLOAD_DIR_REPLY].tuple;
	u32 time_stamp = mtk_r32(eth, 0x0010) & (0x7fff);
	u32 ohash, rhash;
	struct mtk_foe_entry orig = {
		.bfib1.time_stamp = time_stamp,
		.bfib1.psn = 0,
	};
	struct mtk_foe_entry reply = {
		.bfib1.time_stamp = time_stamp,
		.bfib1.psn = 0,
	};

	if (otuple->l4proto != IPPROTO_TCP && otuple->l4proto != IPPROTO_UDP)
		return -EINVAL;
	
	if (type == FLOW_OFFLOAD_DEL) {
		flow = NULL;
		synchronize_rcu();
		return 0;
	}

	switch (otuple->l3proto) {
	case AF_INET:
		if (mtk_foe_prepare_v4(&orig, otuple, rtuple, src, dest) ||
		    mtk_foe_prepare_v4(&reply, rtuple, otuple, dest, src))
			return -EINVAL;

		ohash = mtk_flow_hash_v4(otuple);
		rhash = mtk_flow_hash_v4(rtuple);
		break;

	case AF_INET6:
		return -EINVAL;

	default:
		return -EINVAL;
	}

	/* Two-way hash: when hash collision occurs, the hash value will be shifted to the next position. */
	if (!mtk_check_entry_available(eth, ohash)){       
		if (!mtk_check_entry_available(eth, ohash + 1))
			return -EINVAL;
                ohash += 1;
        }
        if (!mtk_check_entry_available(eth, rhash)){
		if (!mtk_check_entry_available(eth, rhash + 1))
                        return -EINVAL;
                rhash += 1;
	}

	mtk_foe_set_mac(&orig, dest->eth_src, dest->eth_dest);
	mtk_foe_set_mac(&reply, src->eth_src, src->eth_dest);
	mtk_foe_write(eth, ohash, &orig);
	mtk_foe_write(eth, rhash, &reply);
	rcu_assign_pointer(eth->foe_flow_table[ohash], flow);
	rcu_assign_pointer(eth->foe_flow_table[rhash], flow);

	return 0;
}