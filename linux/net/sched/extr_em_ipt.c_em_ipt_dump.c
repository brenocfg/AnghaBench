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
struct tcf_ematch {scalar_t__ data; } ;
struct sk_buff {int dummy; } ;
struct em_ipt_match {int /*<<< orphan*/  match_data; TYPE_1__* match; int /*<<< orphan*/  nfproto; int /*<<< orphan*/  hook; } ;
struct TYPE_2__ {int /*<<< orphan*/  matchsize; scalar_t__ usersize; int /*<<< orphan*/  revision; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  TCA_EM_IPT_HOOK ; 
 int /*<<< orphan*/  TCA_EM_IPT_MATCH_DATA ; 
 int /*<<< orphan*/  TCA_EM_IPT_MATCH_NAME ; 
 int /*<<< orphan*/  TCA_EM_IPT_MATCH_REVISION ; 
 int /*<<< orphan*/  TCA_EM_IPT_NFPROTO ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int em_ipt_dump(struct sk_buff *skb, struct tcf_ematch *em)
{
	struct em_ipt_match *im = (void *)em->data;

	if (nla_put_string(skb, TCA_EM_IPT_MATCH_NAME, im->match->name) < 0)
		return -EMSGSIZE;
	if (nla_put_u32(skb, TCA_EM_IPT_HOOK, im->hook) < 0)
		return -EMSGSIZE;
	if (nla_put_u8(skb, TCA_EM_IPT_MATCH_REVISION, im->match->revision) < 0)
		return -EMSGSIZE;
	if (nla_put_u8(skb, TCA_EM_IPT_NFPROTO, im->nfproto) < 0)
		return -EMSGSIZE;
	if (nla_put(skb, TCA_EM_IPT_MATCH_DATA,
		    im->match->usersize ?: im->match->matchsize,
		    im->match_data) < 0)
		return -EMSGSIZE;

	return 0;
}