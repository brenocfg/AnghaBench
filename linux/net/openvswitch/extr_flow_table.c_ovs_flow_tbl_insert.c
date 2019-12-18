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
struct sw_flow_mask {int dummy; } ;
struct sw_flow {int /*<<< orphan*/  id; } ;
struct flow_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  flow_key_insert (struct flow_table*,struct sw_flow*) ; 
 int flow_mask_insert (struct flow_table*,struct sw_flow*,struct sw_flow_mask const*) ; 
 int /*<<< orphan*/  flow_ufid_insert (struct flow_table*,struct sw_flow*) ; 
 scalar_t__ ovs_identifier_is_ufid (int /*<<< orphan*/ *) ; 

int ovs_flow_tbl_insert(struct flow_table *table, struct sw_flow *flow,
			const struct sw_flow_mask *mask)
{
	int err;

	err = flow_mask_insert(table, flow, mask);
	if (err)
		return err;
	flow_key_insert(table, flow);
	if (ovs_identifier_is_ufid(&flow->id))
		flow_ufid_insert(table, flow);

	return 0;
}