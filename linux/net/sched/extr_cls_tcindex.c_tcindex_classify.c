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
struct tcf_result {int /*<<< orphan*/  classid; scalar_t__ class; } ;
struct tcindex_filter_result {int /*<<< orphan*/  exts; struct tcf_result res; } ;
struct tcindex_data {int mask; int shift; int /*<<< orphan*/  fall_through; } ;
struct tcf_proto {TYPE_1__* chain; int /*<<< orphan*/  root; } ;
struct sk_buff {int tc_index; } ;
struct Qdisc {int /*<<< orphan*/  handle; } ;
struct TYPE_2__ {int /*<<< orphan*/  block; } ;

/* Variables and functions */
 int /*<<< orphan*/  TC_H_MAJ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TC_H_MAKE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,struct sk_buff*,...) ; 
 struct tcindex_data* rcu_dereference_bh (int /*<<< orphan*/ ) ; 
 struct Qdisc* tcf_block_q (int /*<<< orphan*/ ) ; 
 int tcf_exts_exec (struct sk_buff*,int /*<<< orphan*/ *,struct tcf_result*) ; 
 struct tcindex_filter_result* tcindex_lookup (struct tcindex_data*,int) ; 

__attribute__((used)) static int tcindex_classify(struct sk_buff *skb, const struct tcf_proto *tp,
			    struct tcf_result *res)
{
	struct tcindex_data *p = rcu_dereference_bh(tp->root);
	struct tcindex_filter_result *f;
	int key = (skb->tc_index & p->mask) >> p->shift;

	pr_debug("tcindex_classify(skb %p,tp %p,res %p),p %p\n",
		 skb, tp, res, p);

	f = tcindex_lookup(p, key);
	if (!f) {
		struct Qdisc *q = tcf_block_q(tp->chain->block);

		if (!p->fall_through)
			return -1;
		res->classid = TC_H_MAKE(TC_H_MAJ(q->handle), key);
		res->class = 0;
		pr_debug("alg 0x%x\n", res->classid);
		return 0;
	}
	*res = f->res;
	pr_debug("map 0x%x\n", res->classid);

	return tcf_exts_exec(skb, &f->exts, res);
}