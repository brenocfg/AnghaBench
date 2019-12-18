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
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct devlink_dpipe_table {int /*<<< orphan*/  priv; TYPE_1__* table_ops; } ;
struct TYPE_2__ {scalar_t__ (* matches_dump ) (int /*<<< orphan*/ ,struct sk_buff*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_ATTR_DPIPE_TABLE_MATCHES ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static int devlink_dpipe_matches_put(struct devlink_dpipe_table *table,
				     struct sk_buff *skb)
{
	struct nlattr *matches_attr;

	matches_attr = nla_nest_start_noflag(skb,
					     DEVLINK_ATTR_DPIPE_TABLE_MATCHES);
	if (!matches_attr)
		return -EMSGSIZE;

	if (table->table_ops->matches_dump(table->priv, skb))
		goto nla_put_failure;

	nla_nest_end(skb, matches_attr);
	return 0;

nla_put_failure:
	nla_nest_cancel(skb, matches_attr);
	return -EMSGSIZE;
}