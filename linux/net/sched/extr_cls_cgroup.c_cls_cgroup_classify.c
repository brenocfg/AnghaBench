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
typedef  scalar_t__ u32 ;
struct tcf_result {scalar_t__ class; scalar_t__ classid; } ;
struct tcf_proto {int /*<<< orphan*/  root; } ;
struct sk_buff {int dummy; } ;
struct cls_cgroup_head {int /*<<< orphan*/  exts; int /*<<< orphan*/  ematches; } ;

/* Variables and functions */
 struct cls_cgroup_head* rcu_dereference_bh (int /*<<< orphan*/ ) ; 
 scalar_t__ task_get_classid (struct sk_buff*) ; 
 int /*<<< orphan*/  tcf_em_tree_match (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int tcf_exts_exec (struct sk_buff*,int /*<<< orphan*/ *,struct tcf_result*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int cls_cgroup_classify(struct sk_buff *skb, const struct tcf_proto *tp,
			       struct tcf_result *res)
{
	struct cls_cgroup_head *head = rcu_dereference_bh(tp->root);
	u32 classid = task_get_classid(skb);

	if (unlikely(!head))
		return -1;
	if (!classid)
		return -1;
	if (!tcf_em_tree_match(skb, &head->ematches, NULL))
		return -1;

	res->classid = classid;
	res->class = 0;

	return tcf_exts_exec(skb, &head->exts, res);
}