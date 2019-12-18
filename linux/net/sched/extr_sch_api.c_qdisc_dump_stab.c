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
struct sk_buff {int len; } ;
struct qdisc_size_table {int /*<<< orphan*/  szopts; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCA_STAB ; 
 int /*<<< orphan*/  TCA_STAB_BASE ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qdisc_dump_stab(struct sk_buff *skb, struct qdisc_size_table *stab)
{
	struct nlattr *nest;

	nest = nla_nest_start_noflag(skb, TCA_STAB);
	if (nest == NULL)
		goto nla_put_failure;
	if (nla_put(skb, TCA_STAB_BASE, sizeof(stab->szopts), &stab->szopts))
		goto nla_put_failure;
	nla_nest_end(skb, nest);

	return skb->len;

nla_put_failure:
	return -1;
}