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

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  OVS_ACTION_ATTR_CLONE ; 
 int /*<<< orphan*/  nla_data (struct nlattr const*) ; 
 int nla_len (struct nlattr const*) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int ovs_nla_put_actions (int /*<<< orphan*/ ,int,struct sk_buff*) ; 

__attribute__((used)) static int clone_action_to_attr(const struct nlattr *attr,
				struct sk_buff *skb)
{
	struct nlattr *start;
	int err = 0, rem = nla_len(attr);

	start = nla_nest_start_noflag(skb, OVS_ACTION_ATTR_CLONE);
	if (!start)
		return -EMSGSIZE;

	err = ovs_nla_put_actions(nla_data(attr), rem, skb);

	if (err)
		nla_nest_cancel(skb, start);
	else
		nla_nest_end(skb, start);

	return err;
}