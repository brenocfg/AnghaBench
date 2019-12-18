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
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct nf_ct_seqadj {int /*<<< orphan*/  offset_after; int /*<<< orphan*/  offset_before; int /*<<< orphan*/  correction_pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTA_SEQADJ_CORRECTION_POS ; 
 int /*<<< orphan*/  CTA_SEQADJ_OFFSET_AFTER ; 
 int /*<<< orphan*/  CTA_SEQADJ_OFFSET_BEFORE ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int) ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dump_ct_seq_adj(struct sk_buff *skb, const struct nf_ct_seqadj *seq, int type)
{
	struct nlattr *nest_parms;

	nest_parms = nla_nest_start(skb, type);
	if (!nest_parms)
		goto nla_put_failure;

	if (nla_put_be32(skb, CTA_SEQADJ_CORRECTION_POS,
			 htonl(seq->correction_pos)) ||
	    nla_put_be32(skb, CTA_SEQADJ_OFFSET_BEFORE,
			 htonl(seq->offset_before)) ||
	    nla_put_be32(skb, CTA_SEQADJ_OFFSET_AFTER,
			 htonl(seq->offset_after)))
		goto nla_put_failure;

	nla_nest_end(skb, nest_parms);

	return 0;

nla_put_failure:
	return -1;
}