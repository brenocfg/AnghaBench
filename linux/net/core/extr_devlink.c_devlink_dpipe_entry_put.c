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
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct devlink_dpipe_entry {int /*<<< orphan*/  action_values_count; int /*<<< orphan*/  action_values; int /*<<< orphan*/  match_values_count; int /*<<< orphan*/  match_values; int /*<<< orphan*/  counter; scalar_t__ counter_valid; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_ATTR_DPIPE_ENTRY ; 
 int /*<<< orphan*/  DEVLINK_ATTR_DPIPE_ENTRY_ACTION_VALUES ; 
 int /*<<< orphan*/  DEVLINK_ATTR_DPIPE_ENTRY_COUNTER ; 
 int /*<<< orphan*/  DEVLINK_ATTR_DPIPE_ENTRY_INDEX ; 
 int /*<<< orphan*/  DEVLINK_ATTR_DPIPE_ENTRY_MATCH_VALUES ; 
 int /*<<< orphan*/  DEVLINK_ATTR_PAD ; 
 int EMSGSIZE ; 
 int devlink_dpipe_action_values_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devlink_dpipe_match_values_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u64_64bit (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int devlink_dpipe_entry_put(struct sk_buff *skb,
				   struct devlink_dpipe_entry *entry)
{
	struct nlattr *entry_attr, *matches_attr, *actions_attr;
	int err;

	entry_attr = nla_nest_start_noflag(skb, DEVLINK_ATTR_DPIPE_ENTRY);
	if (!entry_attr)
		return  -EMSGSIZE;

	if (nla_put_u64_64bit(skb, DEVLINK_ATTR_DPIPE_ENTRY_INDEX, entry->index,
			      DEVLINK_ATTR_PAD))
		goto nla_put_failure;
	if (entry->counter_valid)
		if (nla_put_u64_64bit(skb, DEVLINK_ATTR_DPIPE_ENTRY_COUNTER,
				      entry->counter, DEVLINK_ATTR_PAD))
			goto nla_put_failure;

	matches_attr = nla_nest_start_noflag(skb,
					     DEVLINK_ATTR_DPIPE_ENTRY_MATCH_VALUES);
	if (!matches_attr)
		goto nla_put_failure;

	err = devlink_dpipe_match_values_put(skb, entry->match_values,
					     entry->match_values_count);
	if (err) {
		nla_nest_cancel(skb, matches_attr);
		goto err_match_values_put;
	}
	nla_nest_end(skb, matches_attr);

	actions_attr = nla_nest_start_noflag(skb,
					     DEVLINK_ATTR_DPIPE_ENTRY_ACTION_VALUES);
	if (!actions_attr)
		goto nla_put_failure;

	err = devlink_dpipe_action_values_put(skb, entry->action_values,
					      entry->action_values_count);
	if (err) {
		nla_nest_cancel(skb, actions_attr);
		goto err_action_values_put;
	}
	nla_nest_end(skb, actions_attr);

	nla_nest_end(skb, entry_attr);
	return 0;

nla_put_failure:
	err = -EMSGSIZE;
err_match_values_put:
err_action_values_put:
	nla_nest_cancel(skb, entry_attr);
	return err;
}