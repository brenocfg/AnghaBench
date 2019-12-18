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
struct tcf_proto {int dummy; } ;
struct tcf_defact {int /*<<< orphan*/  tcf_lock; int /*<<< orphan*/  tcfd_defdata; } ;
struct tcf_chain {int dummy; } ;
struct tc_defact {int /*<<< orphan*/  action; } ;
struct tc_action {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIMP_MAX_DATA ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_strlcpy (int /*<<< orphan*/ ,struct nlattr const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int tcf_action_check_ctrlact (int /*<<< orphan*/ ,struct tcf_proto*,struct tcf_chain**,struct netlink_ext_ack*) ; 
 struct tcf_chain* tcf_action_set_ctrlact (struct tc_action*,int /*<<< orphan*/ ,struct tcf_chain*) ; 
 int /*<<< orphan*/  tcf_chain_put_by_act (struct tcf_chain*) ; 
 struct tcf_defact* to_defact (struct tc_action*) ; 

__attribute__((used)) static int reset_policy(struct tc_action *a, const struct nlattr *defdata,
			struct tc_defact *p, struct tcf_proto *tp,
			struct netlink_ext_ack *extack)
{
	struct tcf_chain *goto_ch = NULL;
	struct tcf_defact *d;
	int err;

	err = tcf_action_check_ctrlact(p->action, tp, &goto_ch, extack);
	if (err < 0)
		return err;
	d = to_defact(a);
	spin_lock_bh(&d->tcf_lock);
	goto_ch = tcf_action_set_ctrlact(a, p->action, goto_ch);
	memset(d->tcfd_defdata, 0, SIMP_MAX_DATA);
	nla_strlcpy(d->tcfd_defdata, defdata, SIMP_MAX_DATA);
	spin_unlock_bh(&d->tcf_lock);
	if (goto_ch)
		tcf_chain_put_by_act(goto_ch);
	return 0;
}