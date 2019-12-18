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
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct devlink_dpipe_table {int /*<<< orphan*/  resource_units; int /*<<< orphan*/  resource_id; scalar_t__ resource_valid; int /*<<< orphan*/  counters_enabled; int /*<<< orphan*/  name; int /*<<< orphan*/  priv; TYPE_1__* table_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* size_get ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_ATTR_DPIPE_TABLE ; 
 int /*<<< orphan*/  DEVLINK_ATTR_DPIPE_TABLE_COUNTERS_ENABLED ; 
 int /*<<< orphan*/  DEVLINK_ATTR_DPIPE_TABLE_NAME ; 
 int /*<<< orphan*/  DEVLINK_ATTR_DPIPE_TABLE_RESOURCE_ID ; 
 int /*<<< orphan*/  DEVLINK_ATTR_DPIPE_TABLE_RESOURCE_UNITS ; 
 int /*<<< orphan*/  DEVLINK_ATTR_DPIPE_TABLE_SIZE ; 
 int /*<<< orphan*/  DEVLINK_ATTR_PAD ; 
 int EMSGSIZE ; 
 scalar_t__ devlink_dpipe_actions_put (struct devlink_dpipe_table*,struct sk_buff*) ; 
 scalar_t__ devlink_dpipe_matches_put (struct devlink_dpipe_table*,struct sk_buff*) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u64_64bit (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int devlink_dpipe_table_put(struct sk_buff *skb,
				   struct devlink_dpipe_table *table)
{
	struct nlattr *table_attr;
	u64 table_size;

	table_size = table->table_ops->size_get(table->priv);
	table_attr = nla_nest_start_noflag(skb, DEVLINK_ATTR_DPIPE_TABLE);
	if (!table_attr)
		return -EMSGSIZE;

	if (nla_put_string(skb, DEVLINK_ATTR_DPIPE_TABLE_NAME, table->name) ||
	    nla_put_u64_64bit(skb, DEVLINK_ATTR_DPIPE_TABLE_SIZE, table_size,
			      DEVLINK_ATTR_PAD))
		goto nla_put_failure;
	if (nla_put_u8(skb, DEVLINK_ATTR_DPIPE_TABLE_COUNTERS_ENABLED,
		       table->counters_enabled))
		goto nla_put_failure;

	if (table->resource_valid) {
		if (nla_put_u64_64bit(skb, DEVLINK_ATTR_DPIPE_TABLE_RESOURCE_ID,
				      table->resource_id, DEVLINK_ATTR_PAD) ||
		    nla_put_u64_64bit(skb, DEVLINK_ATTR_DPIPE_TABLE_RESOURCE_UNITS,
				      table->resource_units, DEVLINK_ATTR_PAD))
			goto nla_put_failure;
	}
	if (devlink_dpipe_matches_put(table, skb))
		goto nla_put_failure;

	if (devlink_dpipe_actions_put(table, skb))
		goto nla_put_failure;

	nla_nest_end(skb, table_attr);
	return 0;

nla_put_failure:
	nla_nest_cancel(skb, table_attr);
	return -EMSGSIZE;
}