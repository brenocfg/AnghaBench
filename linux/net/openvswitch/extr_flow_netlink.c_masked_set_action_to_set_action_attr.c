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
 int /*<<< orphan*/  OVS_ACTION_ATTR_SET ; 
 struct nlattr* nla_data (struct nlattr const*) ; 
 int nla_len (struct nlattr const*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,size_t,struct nlattr*) ; 
 int /*<<< orphan*/  nla_type (struct nlattr const*) ; 

__attribute__((used)) static int masked_set_action_to_set_action_attr(const struct nlattr *a,
						struct sk_buff *skb)
{
	const struct nlattr *ovs_key = nla_data(a);
	struct nlattr *nla;
	size_t key_len = nla_len(ovs_key) / 2;

	/* Revert the conversion we did from a non-masked set action to
	 * masked set action.
	 */
	nla = nla_nest_start_noflag(skb, OVS_ACTION_ATTR_SET);
	if (!nla)
		return -EMSGSIZE;

	if (nla_put(skb, nla_type(ovs_key), key_len, nla_data(ovs_key)))
		return -EMSGSIZE;

	nla_nest_end(skb, nla);
	return 0;
}