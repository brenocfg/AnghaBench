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
struct sw_flow_match {int /*<<< orphan*/  range; int /*<<< orphan*/  key; } ;
struct sw_flow {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int flow_cmp_masked_key (struct sw_flow const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ovs_flow_cmp_unmasked_key (struct sw_flow const*,struct sw_flow_match const*) ; 
 scalar_t__ ovs_identifier_is_ufid (int /*<<< orphan*/ *) ; 

bool ovs_flow_cmp(const struct sw_flow *flow, const struct sw_flow_match *match)
{
	if (ovs_identifier_is_ufid(&flow->id))
		return flow_cmp_masked_key(flow, match->key, &match->range);

	return ovs_flow_cmp_unmasked_key(flow, match);
}