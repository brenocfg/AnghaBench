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
struct tcmsg {int /*<<< orphan*/  tcm_handle; } ;
struct tcf_proto {int dummy; } ;
struct sk_buff {int len; } ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_2__ {scalar_t__ classid; } ;
struct basic_filter {int /*<<< orphan*/  exts; int /*<<< orphan*/  ematches; TYPE_1__ res; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCA_BASIC_CLASSID ; 
 int /*<<< orphan*/  TCA_BASIC_EMATCHES ; 
 int /*<<< orphan*/  TCA_OPTIONS ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ tcf_em_tree_dump (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ tcf_exts_dump (struct sk_buff*,int /*<<< orphan*/ *) ; 
 scalar_t__ tcf_exts_dump_stats (struct sk_buff*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int basic_dump(struct net *net, struct tcf_proto *tp, void *fh,
		      struct sk_buff *skb, struct tcmsg *t)
{
	struct basic_filter *f = fh;
	struct nlattr *nest;

	if (f == NULL)
		return skb->len;

	t->tcm_handle = f->handle;

	nest = nla_nest_start(skb, TCA_OPTIONS);
	if (nest == NULL)
		goto nla_put_failure;

	if (f->res.classid &&
	    nla_put_u32(skb, TCA_BASIC_CLASSID, f->res.classid))
		goto nla_put_failure;

	if (tcf_exts_dump(skb, &f->exts) < 0 ||
	    tcf_em_tree_dump(skb, &f->ematches, TCA_BASIC_EMATCHES) < 0)
		goto nla_put_failure;

	nla_nest_end(skb, nest);

	if (tcf_exts_dump_stats(skb, &f->exts) < 0)
		goto nla_put_failure;

	return skb->len;

nla_put_failure:
	nla_nest_cancel(skb, nest);
	return -1;
}