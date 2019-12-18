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
struct tc_cookie {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct tc_action {int /*<<< orphan*/  act_cookie; TYPE_1__* ops; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  kind; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TCA_ACT_COOKIE ; 
 int /*<<< orphan*/  TCA_KIND ; 
 int /*<<< orphan*/  TCA_OPTIONS ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_trim (struct sk_buff*,unsigned char*) ; 
 struct tc_cookie* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 
 scalar_t__ tcf_action_copy_stats (struct sk_buff*,struct tc_action*,int /*<<< orphan*/ ) ; 
 int tcf_action_dump_old (struct sk_buff*,struct tc_action*,int,int) ; 

int
tcf_action_dump_1(struct sk_buff *skb, struct tc_action *a, int bind, int ref)
{
	int err = -EINVAL;
	unsigned char *b = skb_tail_pointer(skb);
	struct nlattr *nest;
	struct tc_cookie *cookie;

	if (nla_put_string(skb, TCA_KIND, a->ops->kind))
		goto nla_put_failure;
	if (tcf_action_copy_stats(skb, a, 0))
		goto nla_put_failure;

	rcu_read_lock();
	cookie = rcu_dereference(a->act_cookie);
	if (cookie) {
		if (nla_put(skb, TCA_ACT_COOKIE, cookie->len, cookie->data)) {
			rcu_read_unlock();
			goto nla_put_failure;
		}
	}
	rcu_read_unlock();

	nest = nla_nest_start_noflag(skb, TCA_OPTIONS);
	if (nest == NULL)
		goto nla_put_failure;
	err = tcf_action_dump_old(skb, a, bind, ref);
	if (err > 0) {
		nla_nest_end(skb, nest);
		return err;
	}

nla_put_failure:
	nlmsg_trim(skb, b);
	return -1;
}