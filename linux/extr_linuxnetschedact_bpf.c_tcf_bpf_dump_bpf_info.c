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
struct tcf_bpf {int bpf_num_ops; int /*<<< orphan*/  bpf_ops; } ;
struct sock_filter {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  TCA_ACT_BPF_OPS ; 
 int /*<<< orphan*/  TCA_ACT_BPF_OPS_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  nla_len (struct nlattr*) ; 
 scalar_t__ nla_put_u16 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 struct nlattr* nla_reserve (struct sk_buff*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tcf_bpf_dump_bpf_info(const struct tcf_bpf *prog,
				 struct sk_buff *skb)
{
	struct nlattr *nla;

	if (nla_put_u16(skb, TCA_ACT_BPF_OPS_LEN, prog->bpf_num_ops))
		return -EMSGSIZE;

	nla = nla_reserve(skb, TCA_ACT_BPF_OPS, prog->bpf_num_ops *
			  sizeof(struct sock_filter));
	if (nla == NULL)
		return -EMSGSIZE;

	memcpy(nla_data(nla), prog->bpf_ops, nla_len(nla));

	return 0;
}