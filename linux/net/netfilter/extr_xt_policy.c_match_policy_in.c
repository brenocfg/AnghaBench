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
struct xt_policy_info {int flags; int len; struct xt_policy_elem* pol; } ;
struct xt_policy_elem {int dummy; } ;
struct sk_buff {int dummy; } ;
struct sec_path {int len; int /*<<< orphan*/ * xvec; } ;

/* Variables and functions */
 int XT_POLICY_MATCH_STRICT ; 
 scalar_t__ match_xfrm_state (int /*<<< orphan*/ ,struct xt_policy_elem const*,unsigned short) ; 
 struct sec_path* skb_sec_path (struct sk_buff const*) ; 

__attribute__((used)) static int
match_policy_in(const struct sk_buff *skb, const struct xt_policy_info *info,
		unsigned short family)
{
	const struct xt_policy_elem *e;
	const struct sec_path *sp = skb_sec_path(skb);
	int strict = info->flags & XT_POLICY_MATCH_STRICT;
	int i, pos;

	if (sp == NULL)
		return -1;
	if (strict && info->len != sp->len)
		return 0;

	for (i = sp->len - 1; i >= 0; i--) {
		pos = strict ? i - sp->len + 1 : 0;
		if (pos >= info->len)
			return 0;
		e = &info->pol[pos];

		if (match_xfrm_state(sp->xvec[i], e, family)) {
			if (!strict)
				return 1;
		} else if (strict)
			return 0;
	}

	return strict ? 1 : 0;
}