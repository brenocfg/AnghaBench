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
struct devlink_dpipe_value {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_ATTR_DPIPE_MATCH_VALUE ; 
 int EMSGSIZE ; 
 int devlink_dpipe_match_value_put (struct sk_buff*,struct devlink_dpipe_value*) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int devlink_dpipe_match_values_put(struct sk_buff *skb,
					  struct devlink_dpipe_value *values,
					  unsigned int values_count)
{
	struct nlattr *match_attr;
	int i;
	int err;

	for (i = 0; i < values_count; i++) {
		match_attr = nla_nest_start_noflag(skb,
						   DEVLINK_ATTR_DPIPE_MATCH_VALUE);
		if (!match_attr)
			return -EMSGSIZE;
		err = devlink_dpipe_match_value_put(skb, &values[i]);
		if (err)
			goto err_match_value_put;
		nla_nest_end(skb, match_attr);
	}
	return 0;

err_match_value_put:
	nla_nest_cancel(skb, match_attr);
	return err;
}