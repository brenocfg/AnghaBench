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
struct tcf_ematch {int dummy; } ;
struct sk_buff {int dummy; } ;
struct canid_match {int rules_count; int /*<<< orphan*/  rules_raw; } ;
struct can_filter {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 struct canid_match* em_canid_priv (struct tcf_ematch*) ; 
 scalar_t__ nla_put_nohdr (struct sk_buff*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int em_canid_dump(struct sk_buff *skb, struct tcf_ematch *m)
{
	struct canid_match *cm = em_canid_priv(m);

	/*
	 * When configuring this ematch 'rules_count' is set not to exceed
	 * 'rules_raw' array size
	 */
	if (nla_put_nohdr(skb, sizeof(struct can_filter) * cm->rules_count,
	    &cm->rules_raw) < 0)
		return -EMSGSIZE;

	return 0;
}