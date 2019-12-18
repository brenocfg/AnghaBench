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
struct tipc_nl_compat_msg {int /*<<< orphan*/  req; } ;
struct tipc_link_config {int /*<<< orphan*/  name; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  TIPC_NLA_BEARER ; 
 int /*<<< orphan*/  TIPC_NLA_BEARER_NAME ; 
 int /*<<< orphan*/  TIPC_NLA_BEARER_PROP ; 
 scalar_t__ TLV_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __tipc_add_link_prop (struct sk_buff*,struct tipc_nl_compat_msg*,struct tipc_link_config*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tipc_nl_compat_bearer_set(struct sk_buff *skb,
				     struct tipc_nl_compat_msg *msg)
{
	struct nlattr *prop;
	struct nlattr *bearer;
	struct tipc_link_config *lc;

	lc = (struct tipc_link_config *)TLV_DATA(msg->req);

	bearer = nla_nest_start_noflag(skb, TIPC_NLA_BEARER);
	if (!bearer)
		return -EMSGSIZE;

	if (nla_put_string(skb, TIPC_NLA_BEARER_NAME, lc->name))
		return -EMSGSIZE;

	prop = nla_nest_start_noflag(skb, TIPC_NLA_BEARER_PROP);
	if (!prop)
		return -EMSGSIZE;

	__tipc_add_link_prop(skb, msg, lc);
	nla_nest_end(skb, prop);
	nla_nest_end(skb, bearer);

	return 0;
}