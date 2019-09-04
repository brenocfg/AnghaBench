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
struct tcf_bpf {TYPE_2__* filter; scalar_t__ bpf_name; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  tag; TYPE_1__* aux; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  TCA_ACT_BPF_ID ; 
 int /*<<< orphan*/  TCA_ACT_BPF_NAME ; 
 int /*<<< orphan*/  TCA_ACT_BPF_TAG ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  nla_len (struct nlattr*) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nlattr* nla_reserve (struct sk_buff*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tcf_bpf_dump_ebpf_info(const struct tcf_bpf *prog,
				  struct sk_buff *skb)
{
	struct nlattr *nla;

	if (prog->bpf_name &&
	    nla_put_string(skb, TCA_ACT_BPF_NAME, prog->bpf_name))
		return -EMSGSIZE;

	if (nla_put_u32(skb, TCA_ACT_BPF_ID, prog->filter->aux->id))
		return -EMSGSIZE;

	nla = nla_reserve(skb, TCA_ACT_BPF_TAG, sizeof(prog->filter->tag));
	if (nla == NULL)
		return -EMSGSIZE;

	memcpy(nla_data(nla), prog->filter->tag, nla_len(nla));

	return 0;
}