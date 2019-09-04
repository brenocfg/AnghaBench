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
struct tcf_sample {int truncate; int /*<<< orphan*/  tcf_lock; void* trunc_size; int /*<<< orphan*/  psample_group; void* psample_group_num; void* rate; int /*<<< orphan*/  tcf_action; } ;
struct tc_sample {int /*<<< orphan*/  action; int /*<<< orphan*/  index; } ;
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
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,struct psample_group*) ; 
 int /*<<< orphan*/  TCA_SAMPLE_MAX ; 
 size_t TCA_SAMPLE_PARMS ; 
 size_t TCA_SAMPLE_PSAMPLE_GROUP ; 
 size_t TCA_SAMPLE_RATE ; 
 size_t TCA_SAMPLE_TRUNC_SIZE ; 
 int /*<<< orphan*/  act_sample_ops ; 
 struct tc_action_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 struct tc_sample* nla_data (struct nlattr*) ; 
 void* nla_get_u32 (struct nlattr*) ; 
 int nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct psample_group* psample_group_get (struct net*,void*) ; 
 int /*<<< orphan*/  sample_net_id ; 
 int /*<<< orphan*/  sample_policy ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int tcf_idr_check_alloc (struct tc_action_net*,int /*<<< orphan*/ *,struct tc_action**,int) ; 
 int /*<<< orphan*/  tcf_idr_cleanup (struct tc_action_net*,int /*<<< orphan*/ ) ; 
 int tcf_idr_create (struct tc_action_net*,int /*<<< orphan*/ ,struct nlattr*,struct tc_action**,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  tcf_idr_insert (struct tc_action_net*,struct tc_action*) ; 
 int /*<<< orphan*/  tcf_idr_release (struct tc_action*,int) ; 
 struct tcf_sample* to_sample (struct tc_action*) ; 

__attribute__((used)) static int tcf_sample_init(struct net *net, struct nlattr *nla,
			   struct nlattr *est, struct tc_action **a, int ovr,
			   int bind, bool rtnl_held,
			   struct netlink_ext_ack *extack)
{
	struct tc_action_net *tn = net_generic(net, sample_net_id);
	struct nlattr *tb[TCA_SAMPLE_MAX + 1];
	struct psample_group *psample_group;
	u32 psample_group_num, rate;
	struct tc_sample *parm;
	struct tcf_sample *s;
	bool exists = false;
	int ret, err;

	if (!nla)
		return -EINVAL;
	ret = nla_parse_nested(tb, TCA_SAMPLE_MAX, nla, sample_policy, NULL);
	if (ret < 0)
		return ret;
	if (!tb[TCA_SAMPLE_PARMS] || !tb[TCA_SAMPLE_RATE] ||
	    !tb[TCA_SAMPLE_PSAMPLE_GROUP])
		return -EINVAL;

	parm = nla_data(tb[TCA_SAMPLE_PARMS]);

	err = tcf_idr_check_alloc(tn, &parm->index, a, bind);
	if (err < 0)
		return err;
	exists = err;
	if (exists && bind)
		return 0;

	if (!exists) {
		ret = tcf_idr_create(tn, parm->index, est, a,
				     &act_sample_ops, bind, true);
		if (ret) {
			tcf_idr_cleanup(tn, parm->index);
			return ret;
		}
		ret = ACT_P_CREATED;
	} else if (!ovr) {
		tcf_idr_release(*a, bind);
		return -EEXIST;
	}

	rate = nla_get_u32(tb[TCA_SAMPLE_RATE]);
	if (!rate) {
		NL_SET_ERR_MSG(extack, "invalid sample rate");
		tcf_idr_release(*a, bind);
		return -EINVAL;
	}
	psample_group_num = nla_get_u32(tb[TCA_SAMPLE_PSAMPLE_GROUP]);
	psample_group = psample_group_get(net, psample_group_num);
	if (!psample_group) {
		tcf_idr_release(*a, bind);
		return -ENOMEM;
	}

	s = to_sample(*a);

	spin_lock_bh(&s->tcf_lock);
	s->tcf_action = parm->action;
	s->rate = rate;
	s->psample_group_num = psample_group_num;
	RCU_INIT_POINTER(s->psample_group, psample_group);

	if (tb[TCA_SAMPLE_TRUNC_SIZE]) {
		s->truncate = true;
		s->trunc_size = nla_get_u32(tb[TCA_SAMPLE_TRUNC_SIZE]);
	}
	spin_unlock_bh(&s->tcf_lock);

	if (ret == ACT_P_CREATED)
		tcf_idr_insert(tn, *a);
	return ret;
}