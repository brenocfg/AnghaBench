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
typedef  scalar_t__ u32 ;
struct tcmsg {int /*<<< orphan*/  tcm_handle; } ;
struct tcf_proto {int dummy; } ;
struct sk_buff {int len; } ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_2__ {scalar_t__ classid; } ;
struct cls_bpf_prog {int /*<<< orphan*/  exts; scalar_t__ gen_flags; scalar_t__ exts_integrated; TYPE_1__ res; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCA_BPF_CLASSID ; 
 int /*<<< orphan*/  TCA_BPF_FLAGS ; 
 int /*<<< orphan*/  TCA_BPF_FLAGS_GEN ; 
 scalar_t__ TCA_BPF_FLAG_ACT_DIRECT ; 
 int /*<<< orphan*/  TCA_OPTIONS ; 
 int cls_bpf_dump_bpf_info (struct cls_bpf_prog*,struct sk_buff*) ; 
 int cls_bpf_dump_ebpf_info (struct cls_bpf_prog*,struct sk_buff*) ; 
 scalar_t__ cls_bpf_is_ebpf (struct cls_bpf_prog*) ; 
 int /*<<< orphan*/  cls_bpf_offload_update_stats (struct tcf_proto*,struct cls_bpf_prog*) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ tcf_exts_dump (struct sk_buff*,int /*<<< orphan*/ *) ; 
 scalar_t__ tcf_exts_dump_stats (struct sk_buff*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cls_bpf_dump(struct net *net, struct tcf_proto *tp, void *fh,
			struct sk_buff *skb, struct tcmsg *tm, bool rtnl_held)
{
	struct cls_bpf_prog *prog = fh;
	struct nlattr *nest;
	u32 bpf_flags = 0;
	int ret;

	if (prog == NULL)
		return skb->len;

	tm->tcm_handle = prog->handle;

	cls_bpf_offload_update_stats(tp, prog);

	nest = nla_nest_start_noflag(skb, TCA_OPTIONS);
	if (nest == NULL)
		goto nla_put_failure;

	if (prog->res.classid &&
	    nla_put_u32(skb, TCA_BPF_CLASSID, prog->res.classid))
		goto nla_put_failure;

	if (cls_bpf_is_ebpf(prog))
		ret = cls_bpf_dump_ebpf_info(prog, skb);
	else
		ret = cls_bpf_dump_bpf_info(prog, skb);
	if (ret)
		goto nla_put_failure;

	if (tcf_exts_dump(skb, &prog->exts) < 0)
		goto nla_put_failure;

	if (prog->exts_integrated)
		bpf_flags |= TCA_BPF_FLAG_ACT_DIRECT;
	if (bpf_flags && nla_put_u32(skb, TCA_BPF_FLAGS, bpf_flags))
		goto nla_put_failure;
	if (prog->gen_flags &&
	    nla_put_u32(skb, TCA_BPF_FLAGS_GEN, prog->gen_flags))
		goto nla_put_failure;

	nla_nest_end(skb, nest);

	if (tcf_exts_dump_stats(skb, &prog->exts) < 0)
		goto nla_put_failure;

	return skb->len;

nla_put_failure:
	nla_nest_cancel(skb, nest);
	return -1;
}