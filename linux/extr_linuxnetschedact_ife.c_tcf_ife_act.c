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
struct tcf_result {int dummy; } ;
struct tcf_ife_params {int flags; } ;
struct tcf_ife_info {int /*<<< orphan*/  params; } ;
struct tc_action {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int IFE_ENCODE ; 
 struct tcf_ife_params* rcu_dereference_bh (int /*<<< orphan*/ ) ; 
 int tcf_ife_decode (struct sk_buff*,struct tc_action const*,struct tcf_result*) ; 
 int tcf_ife_encode (struct sk_buff*,struct tc_action const*,struct tcf_result*,struct tcf_ife_params*) ; 
 struct tcf_ife_info* to_ife (struct tc_action const*) ; 

__attribute__((used)) static int tcf_ife_act(struct sk_buff *skb, const struct tc_action *a,
		       struct tcf_result *res)
{
	struct tcf_ife_info *ife = to_ife(a);
	struct tcf_ife_params *p;
	int ret;

	p = rcu_dereference_bh(ife->params);
	if (p->flags & IFE_ENCODE) {
		ret = tcf_ife_encode(skb, a, res, p);
		return ret;
	}

	return tcf_ife_decode(skb, a, res);
}