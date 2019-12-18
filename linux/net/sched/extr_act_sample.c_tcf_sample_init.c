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
typedef  void* u32 ;
struct tcf_sample {int truncate; int /*<<< orphan*/  tcf_lock; void* trunc_size; int /*<<< orphan*/  psample_group; void* psample_group_num; void* rate; } ;
struct tcf_proto {int dummy; } ;
struct tcf_chain {int dummy; } ;
struct tc_sample {int /*<<< orphan*/  action; void* index; } ;
struct tc_action_net {int dummy; } ;
struct tc_action {int dummy; } ;
struct psample_group {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int ACT_P_CREATED ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  TCA_SAMPLE_MAX ; 
 size_t TCA_SAMPLE_PARMS ; 
 size_t TCA_SAMPLE_PSAMPLE_GROUP ; 
 size_t TCA_SAMPLE_RATE ; 
 size_t TCA_SAMPLE_TRUNC_SIZE ; 
 int /*<<< orphan*/  act_sample_ops ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct tc_action_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 struct tc_sample* nla_data (struct nlattr*) ; 
 void* nla_get_u32 (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct psample_group* psample_group_get (struct net*,void*) ; 
 int /*<<< orphan*/  psample_group_put (struct psample_group*) ; 
 int /*<<< orphan*/  rcu_swap_protected (int /*<<< orphan*/ ,struct psample_group*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sample_net_id ; 
 int /*<<< orphan*/  sample_policy ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int tcf_action_check_ctrlact (int /*<<< orphan*/ ,struct tcf_proto*,struct tcf_chain**,struct netlink_ext_ack*) ; 
 struct tcf_chain* tcf_action_set_ctrlact (struct tc_action*,int /*<<< orphan*/ ,struct tcf_chain*) ; 
 int /*<<< orphan*/  tcf_chain_put_by_act (struct tcf_chain*) ; 
 int tcf_idr_check_alloc (struct tc_action_net*,void**,struct tc_action**,int) ; 
 int /*<<< orphan*/  tcf_idr_cleanup (struct tc_action_net*,void*) ; 
 int tcf_idr_create (struct tc_action_net*,void*,struct nlattr*,struct tc_action**,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  tcf_idr_insert (struct tc_action_net*,struct tc_action*) ; 
 int /*<<< orphan*/  tcf_idr_release (struct tc_action*,int) ; 
 struct tcf_sample* to_sample (struct tc_action*) ; 

__attribute__((used)) static int tcf_sample_init(struct net *net, struct nlattr *nla,
			   struct nlattr *est, struct tc_action **a, int ovr,
			   int bind, bool rtnl_held, struct tcf_proto *tp,
			   struct netlink_ext_ack *extack)
{
	struct tc_action_net *tn = net_generic(net, sample_net_id);
	struct nlattr *tb[TCA_SAMPLE_MAX + 1];
	struct psample_group *psample_group;
	u32 psample_group_num, rate, index;
	struct tcf_chain *goto_ch = NULL;
	struct tc_sample *parm;
	struct tcf_sample *s;
	bool exists = false;
	int ret, err;

	if (!nla)
		return -EINVAL;
	ret = nla_parse_nested_deprecated(tb, TCA_SAMPLE_MAX, nla,
					  sample_policy, NULL);
	if (ret < 0)
		return ret;
	if (!tb[TCA_SAMPLE_PARMS] || !tb[TCA_SAMPLE_RATE] ||
	    !tb[TCA_SAMPLE_PSAMPLE_GROUP])
		return -EINVAL;

	parm = nla_data(tb[TCA_SAMPLE_PARMS]);
	index = parm->index;
	err = tcf_idr_check_alloc(tn, &index, a, bind);
	if (err < 0)
		return err;
	exists = err;
	if (exists && bind)
		return 0;

	if (!exists) {
		ret = tcf_idr_create(tn, index, est, a,
				     &act_sample_ops, bind, true);
		if (ret) {
			tcf_idr_cleanup(tn, index);
			return ret;
		}
		ret = ACT_P_CREATED;
	} else if (!ovr) {
		tcf_idr_release(*a, bind);
		return -EEXIST;
	}
	err = tcf_action_check_ctrlact(parm->action, tp, &goto_ch, extack);
	if (err < 0)
		goto release_idr;

	rate = nla_get_u32(tb[TCA_SAMPLE_RATE]);
	if (!rate) {
		NL_SET_ERR_MSG(extack, "invalid sample rate");
		err = -EINVAL;
		goto put_chain;
	}
	psample_group_num = nla_get_u32(tb[TCA_SAMPLE_PSAMPLE_GROUP]);
	psample_group = psample_group_get(net, psample_group_num);
	if (!psample_group) {
		err = -ENOMEM;
		goto put_chain;
	}

	s = to_sample(*a);

	spin_lock_bh(&s->tcf_lock);
	goto_ch = tcf_action_set_ctrlact(*a, parm->action, goto_ch);
	s->rate = rate;
	s->psample_group_num = psample_group_num;
	rcu_swap_protected(s->psample_group, psample_group,
			   lockdep_is_held(&s->tcf_lock));

	if (tb[TCA_SAMPLE_TRUNC_SIZE]) {
		s->truncate = true;
		s->trunc_size = nla_get_u32(tb[TCA_SAMPLE_TRUNC_SIZE]);
	}
	spin_unlock_bh(&s->tcf_lock);

	if (psample_group)
		psample_group_put(psample_group);
	if (goto_ch)
		tcf_chain_put_by_act(goto_ch);

	if (ret == ACT_P_CREATED)
		tcf_idr_insert(tn, *a);
	return ret;
put_chain:
	if (goto_ch)
		tcf_chain_put_by_act(goto_ch);
release_idr:
	tcf_idr_release(*a, bind);
	return err;
}