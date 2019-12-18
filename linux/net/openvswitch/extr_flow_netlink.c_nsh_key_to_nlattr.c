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
struct TYPE_2__ {scalar_t__ mdtype; } ;
struct ovs_key_nsh {TYPE_1__* context; TYPE_1__ base; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 scalar_t__ NSH_M_TYPE1 ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_NSH ; 
 int /*<<< orphan*/  OVS_NSH_KEY_ATTR_BASE ; 
 int /*<<< orphan*/  OVS_NSH_KEY_ATTR_MD1 ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,TYPE_1__*) ; 

__attribute__((used)) static int nsh_key_to_nlattr(const struct ovs_key_nsh *nsh, bool is_mask,
			     struct sk_buff *skb)
{
	struct nlattr *start;

	start = nla_nest_start_noflag(skb, OVS_KEY_ATTR_NSH);
	if (!start)
		return -EMSGSIZE;

	if (nla_put(skb, OVS_NSH_KEY_ATTR_BASE, sizeof(nsh->base), &nsh->base))
		goto nla_put_failure;

	if (is_mask || nsh->base.mdtype == NSH_M_TYPE1) {
		if (nla_put(skb, OVS_NSH_KEY_ATTR_MD1,
			    sizeof(nsh->context), nsh->context))
			goto nla_put_failure;
	}

	/* Don't support MD type 2 yet */

	nla_nest_end(skb, start);

	return 0;

nla_put_failure:
	return -EMSGSIZE;
}