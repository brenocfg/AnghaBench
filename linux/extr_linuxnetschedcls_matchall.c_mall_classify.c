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
struct tcf_proto {int /*<<< orphan*/  root; } ;
struct sk_buff {int dummy; } ;
struct cls_mall_head {int /*<<< orphan*/  exts; struct tcf_result res; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 struct cls_mall_head* rcu_dereference_bh (int /*<<< orphan*/ ) ; 
 scalar_t__ tc_skip_sw (int /*<<< orphan*/ ) ; 
 int tcf_exts_exec (struct sk_buff*,int /*<<< orphan*/ *,struct tcf_result*) ; 

__attribute__((used)) static int mall_classify(struct sk_buff *skb, const struct tcf_proto *tp,
			 struct tcf_result *res)
{
	struct cls_mall_head *head = rcu_dereference_bh(tp->root);

	if (tc_skip_sw(head->flags))
		return -1;

	*res = head->res;
	return tcf_exts_exec(skb, &head->exts, res);
}