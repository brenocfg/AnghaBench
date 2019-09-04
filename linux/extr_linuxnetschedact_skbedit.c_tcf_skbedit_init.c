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
typedef  int u64 ;
typedef  int u32 ;
typedef  void* u16 ;
struct tcf_skbedit_params {int flags; int priority; int mark; int mask; void* ptype; void* queue_mapping; } ;
struct tcf_skbedit {int /*<<< orphan*/  params; int /*<<< orphan*/  tcf_action; } ;
struct tc_skbedit {int /*<<< orphan*/  action; int /*<<< orphan*/  index; } ;
struct tc_action_net {int dummy; } ;
struct tc_action {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int ACT_P_CREATED ; 
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SKBEDIT_F_INHERITDSFIELD ; 
 int SKBEDIT_F_MARK ; 
 int SKBEDIT_F_MASK ; 
 int SKBEDIT_F_PRIORITY ; 
 int SKBEDIT_F_PTYPE ; 
 int SKBEDIT_F_QUEUE_MAPPING ; 
 size_t TCA_SKBEDIT_FLAGS ; 
 size_t TCA_SKBEDIT_MARK ; 
 size_t TCA_SKBEDIT_MASK ; 
 int /*<<< orphan*/  TCA_SKBEDIT_MAX ; 
 size_t TCA_SKBEDIT_PARMS ; 
 size_t TCA_SKBEDIT_PRIORITY ; 
 size_t TCA_SKBEDIT_PTYPE ; 
 size_t TCA_SKBEDIT_QUEUE_MAPPING ; 
 int /*<<< orphan*/  act_skbedit_ops ; 
 int /*<<< orphan*/  kfree_rcu (struct tcf_skbedit_params*,int /*<<< orphan*/ ) ; 
 struct tcf_skbedit_params* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct tc_action_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 void* nla_data (struct nlattr*) ; 
 int nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct tcf_skbedit_params*) ; 
 struct tcf_skbedit_params* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pkt_type_ok (void*) ; 
 int /*<<< orphan*/  skbedit_net_id ; 
 int /*<<< orphan*/  skbedit_policy ; 
 int tcf_idr_check_alloc (struct tc_action_net*,int /*<<< orphan*/ *,struct tc_action**,int) ; 
 int /*<<< orphan*/  tcf_idr_cleanup (struct tc_action_net*,int /*<<< orphan*/ ) ; 
 int tcf_idr_create (struct tc_action_net*,int /*<<< orphan*/ ,struct nlattr*,struct tc_action**,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  tcf_idr_insert (struct tc_action_net*,struct tc_action*) ; 
 int /*<<< orphan*/  tcf_idr_release (struct tc_action*,int) ; 
 struct tcf_skbedit* to_skbedit (struct tc_action*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int tcf_skbedit_init(struct net *net, struct nlattr *nla,
			    struct nlattr *est, struct tc_action **a,
			    int ovr, int bind, bool rtnl_held,
			    struct netlink_ext_ack *extack)
{
	struct tc_action_net *tn = net_generic(net, skbedit_net_id);
	struct tcf_skbedit_params *params_old, *params_new;
	struct nlattr *tb[TCA_SKBEDIT_MAX + 1];
	struct tc_skbedit *parm;
	struct tcf_skbedit *d;
	u32 flags = 0, *priority = NULL, *mark = NULL, *mask = NULL;
	u16 *queue_mapping = NULL, *ptype = NULL;
	bool exists = false;
	int ret = 0, err;

	if (nla == NULL)
		return -EINVAL;

	err = nla_parse_nested(tb, TCA_SKBEDIT_MAX, nla, skbedit_policy, NULL);
	if (err < 0)
		return err;

	if (tb[TCA_SKBEDIT_PARMS] == NULL)
		return -EINVAL;

	if (tb[TCA_SKBEDIT_PRIORITY] != NULL) {
		flags |= SKBEDIT_F_PRIORITY;
		priority = nla_data(tb[TCA_SKBEDIT_PRIORITY]);
	}

	if (tb[TCA_SKBEDIT_QUEUE_MAPPING] != NULL) {
		flags |= SKBEDIT_F_QUEUE_MAPPING;
		queue_mapping = nla_data(tb[TCA_SKBEDIT_QUEUE_MAPPING]);
	}

	if (tb[TCA_SKBEDIT_PTYPE] != NULL) {
		ptype = nla_data(tb[TCA_SKBEDIT_PTYPE]);
		if (!skb_pkt_type_ok(*ptype))
			return -EINVAL;
		flags |= SKBEDIT_F_PTYPE;
	}

	if (tb[TCA_SKBEDIT_MARK] != NULL) {
		flags |= SKBEDIT_F_MARK;
		mark = nla_data(tb[TCA_SKBEDIT_MARK]);
	}

	if (tb[TCA_SKBEDIT_MASK] != NULL) {
		flags |= SKBEDIT_F_MASK;
		mask = nla_data(tb[TCA_SKBEDIT_MASK]);
	}

	if (tb[TCA_SKBEDIT_FLAGS] != NULL) {
		u64 *pure_flags = nla_data(tb[TCA_SKBEDIT_FLAGS]);

		if (*pure_flags & SKBEDIT_F_INHERITDSFIELD)
			flags |= SKBEDIT_F_INHERITDSFIELD;
	}

	parm = nla_data(tb[TCA_SKBEDIT_PARMS]);

	err = tcf_idr_check_alloc(tn, &parm->index, a, bind);
	if (err < 0)
		return err;
	exists = err;
	if (exists && bind)
		return 0;

	if (!flags) {
		if (exists)
			tcf_idr_release(*a, bind);
		else
			tcf_idr_cleanup(tn, parm->index);
		return -EINVAL;
	}

	if (!exists) {
		ret = tcf_idr_create(tn, parm->index, est, a,
				     &act_skbedit_ops, bind, true);
		if (ret) {
			tcf_idr_cleanup(tn, parm->index);
			return ret;
		}

		d = to_skbedit(*a);
		ret = ACT_P_CREATED;
	} else {
		d = to_skbedit(*a);
		if (!ovr) {
			tcf_idr_release(*a, bind);
			return -EEXIST;
		}
	}

	ASSERT_RTNL();

	params_new = kzalloc(sizeof(*params_new), GFP_KERNEL);
	if (unlikely(!params_new)) {
		tcf_idr_release(*a, bind);
		return -ENOMEM;
	}

	params_new->flags = flags;
	if (flags & SKBEDIT_F_PRIORITY)
		params_new->priority = *priority;
	if (flags & SKBEDIT_F_QUEUE_MAPPING)
		params_new->queue_mapping = *queue_mapping;
	if (flags & SKBEDIT_F_MARK)
		params_new->mark = *mark;
	if (flags & SKBEDIT_F_PTYPE)
		params_new->ptype = *ptype;
	/* default behaviour is to use all the bits */
	params_new->mask = 0xffffffff;
	if (flags & SKBEDIT_F_MASK)
		params_new->mask = *mask;

	d->tcf_action = parm->action;
	params_old = rtnl_dereference(d->params);
	rcu_assign_pointer(d->params, params_new);
	if (params_old)
		kfree_rcu(params_old, rcu);

	if (ret == ACT_P_CREATED)
		tcf_idr_insert(tn, *a);
	return ret;
}