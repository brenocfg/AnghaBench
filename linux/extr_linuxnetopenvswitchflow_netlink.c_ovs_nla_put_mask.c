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
struct sw_flow {TYPE_1__* mask; int /*<<< orphan*/  key; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  OVS_FLOW_ATTR_MASK ; 
 int ovs_nla_put_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct sk_buff*) ; 

int ovs_nla_put_mask(const struct sw_flow *flow, struct sk_buff *skb)
{
	return ovs_nla_put_key(&flow->key, &flow->mask->key,
				OVS_FLOW_ATTR_MASK, true, skb);
}