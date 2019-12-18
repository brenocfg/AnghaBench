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
struct tcf_proto {int /*<<< orphan*/  root; } ;
struct sk_buff {int len; } ;
struct nlattr {int dummy; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct net {int dummy; } ;
struct fw_head {int mask; } ;
struct TYPE_2__ {int classid; } ;
struct fw_filter {int /*<<< orphan*/  exts; scalar_t__ ifindex; TYPE_1__ res; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCA_FW_CLASSID ; 
 int /*<<< orphan*/  TCA_FW_INDEV ; 
 int /*<<< orphan*/  TCA_FW_MASK ; 
 int /*<<< orphan*/  TCA_OPTIONS ; 
 struct net_device* __dev_get_by_index (struct net*,scalar_t__) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 struct fw_head* rtnl_dereference (int /*<<< orphan*/ ) ; 
 scalar_t__ tcf_exts_dump (struct sk_buff*,int /*<<< orphan*/ *) ; 
 scalar_t__ tcf_exts_dump_stats (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_exts_has_actions (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fw_dump(struct net *net, struct tcf_proto *tp, void *fh,
		   struct sk_buff *skb, struct tcmsg *t, bool rtnl_held)
{
	struct fw_head *head = rtnl_dereference(tp->root);
	struct fw_filter *f = fh;
	struct nlattr *nest;

	if (f == NULL)
		return skb->len;

	t->tcm_handle = f->id;

	if (!f->res.classid && !tcf_exts_has_actions(&f->exts))
		return skb->len;

	nest = nla_nest_start_noflag(skb, TCA_OPTIONS);
	if (nest == NULL)
		goto nla_put_failure;

	if (f->res.classid &&
	    nla_put_u32(skb, TCA_FW_CLASSID, f->res.classid))
		goto nla_put_failure;
	if (f->ifindex) {
		struct net_device *dev;
		dev = __dev_get_by_index(net, f->ifindex);
		if (dev && nla_put_string(skb, TCA_FW_INDEV, dev->name))
			goto nla_put_failure;
	}
	if (head->mask != 0xFFFFFFFF &&
	    nla_put_u32(skb, TCA_FW_MASK, head->mask))
		goto nla_put_failure;

	if (tcf_exts_dump(skb, &f->exts) < 0)
		goto nla_put_failure;

	nla_nest_end(skb, nest);

	if (tcf_exts_dump_stats(skb, &f->exts) < 0)
		goto nla_put_failure;

	return skb->len;

nla_put_failure:
	nla_nest_cancel(skb, nest);
	return -1;
}