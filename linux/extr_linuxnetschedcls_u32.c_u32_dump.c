#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tcmsg {int tcm_handle; } ;
struct tcf_proto {int dummy; } ;
struct TYPE_3__ {int classid; } ;
struct TYPE_4__ {int nkeys; } ;
struct tc_u_knode {int handle; int flags; int /*<<< orphan*/  exts; int /*<<< orphan*/  ht_down; TYPE_1__ res; int /*<<< orphan*/  ht_up; TYPE_2__ sel; } ;
struct tc_u_hnode {int divisor; int handle; } ;
struct tc_u32_key {int dummy; } ;
struct sk_buff {int len; } ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCA_OPTIONS ; 
 int /*<<< orphan*/  TCA_U32_CLASSID ; 
 int /*<<< orphan*/  TCA_U32_DIVISOR ; 
 int /*<<< orphan*/  TCA_U32_FLAGS ; 
 int /*<<< orphan*/  TCA_U32_HASH ; 
 int /*<<< orphan*/  TCA_U32_LINK ; 
 int /*<<< orphan*/  TCA_U32_SEL ; 
 scalar_t__ TC_U32_KEY (int) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 struct tc_u_hnode* rtnl_dereference (int /*<<< orphan*/ ) ; 
 scalar_t__ tcf_exts_dump (struct sk_buff*,int /*<<< orphan*/ *) ; 
 scalar_t__ tcf_exts_dump_stats (struct sk_buff*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int u32_dump(struct net *net, struct tcf_proto *tp, void *fh,
		    struct sk_buff *skb, struct tcmsg *t)
{
	struct tc_u_knode *n = fh;
	struct tc_u_hnode *ht_up, *ht_down;
	struct nlattr *nest;

	if (n == NULL)
		return skb->len;

	t->tcm_handle = n->handle;

	nest = nla_nest_start(skb, TCA_OPTIONS);
	if (nest == NULL)
		goto nla_put_failure;

	if (TC_U32_KEY(n->handle) == 0) {
		struct tc_u_hnode *ht = fh;
		u32 divisor = ht->divisor + 1;

		if (nla_put_u32(skb, TCA_U32_DIVISOR, divisor))
			goto nla_put_failure;
	} else {
#ifdef CONFIG_CLS_U32_PERF
		struct tc_u32_pcnt *gpf;
		int cpu;
#endif

		if (nla_put(skb, TCA_U32_SEL,
			    sizeof(n->sel) + n->sel.nkeys*sizeof(struct tc_u32_key),
			    &n->sel))
			goto nla_put_failure;

		ht_up = rtnl_dereference(n->ht_up);
		if (ht_up) {
			u32 htid = n->handle & 0xFFFFF000;
			if (nla_put_u32(skb, TCA_U32_HASH, htid))
				goto nla_put_failure;
		}
		if (n->res.classid &&
		    nla_put_u32(skb, TCA_U32_CLASSID, n->res.classid))
			goto nla_put_failure;

		ht_down = rtnl_dereference(n->ht_down);
		if (ht_down &&
		    nla_put_u32(skb, TCA_U32_LINK, ht_down->handle))
			goto nla_put_failure;

		if (n->flags && nla_put_u32(skb, TCA_U32_FLAGS, n->flags))
			goto nla_put_failure;

#ifdef CONFIG_CLS_U32_MARK
		if ((n->val || n->mask)) {
			struct tc_u32_mark mark = {.val = n->val,
						   .mask = n->mask,
						   .success = 0};
			int cpum;

			for_each_possible_cpu(cpum) {
				__u32 cnt = *per_cpu_ptr(n->pcpu_success, cpum);

				mark.success += cnt;
			}

			if (nla_put(skb, TCA_U32_MARK, sizeof(mark), &mark))
				goto nla_put_failure;
		}
#endif

		if (tcf_exts_dump(skb, &n->exts) < 0)
			goto nla_put_failure;

#ifdef CONFIG_NET_CLS_IND
		if (n->ifindex) {
			struct net_device *dev;
			dev = __dev_get_by_index(net, n->ifindex);
			if (dev && nla_put_string(skb, TCA_U32_INDEV, dev->name))
				goto nla_put_failure;
		}
#endif
#ifdef CONFIG_CLS_U32_PERF
		gpf = kzalloc(sizeof(struct tc_u32_pcnt) +
			      n->sel.nkeys * sizeof(u64),
			      GFP_KERNEL);
		if (!gpf)
			goto nla_put_failure;

		for_each_possible_cpu(cpu) {
			int i;
			struct tc_u32_pcnt *pf = per_cpu_ptr(n->pf, cpu);

			gpf->rcnt += pf->rcnt;
			gpf->rhit += pf->rhit;
			for (i = 0; i < n->sel.nkeys; i++)
				gpf->kcnts[i] += pf->kcnts[i];
		}

		if (nla_put_64bit(skb, TCA_U32_PCNT,
				  sizeof(struct tc_u32_pcnt) +
				  n->sel.nkeys * sizeof(u64),
				  gpf, TCA_U32_PAD)) {
			kfree(gpf);
			goto nla_put_failure;
		}
		kfree(gpf);
#endif
	}

	nla_nest_end(skb, nest);

	if (TC_U32_KEY(n->handle))
		if (tcf_exts_dump_stats(skb, &n->exts) < 0)
			goto nla_put_failure;
	return skb->len;

nla_put_failure:
	nla_nest_cancel(skb, nest);
	return -1;
}