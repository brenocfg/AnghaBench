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
typedef  int /*<<< orphan*/  u32 ;
struct tcf_proto {int dummy; } ;
struct tcf_mirred {int tcfm_mac_header_xmit; int tcfm_eaction; int /*<<< orphan*/  tcfm_list; int /*<<< orphan*/  tcf_lock; int /*<<< orphan*/  tcfm_dev; } ;
struct tcf_chain {int dummy; } ;
struct tc_mirred {int eaction; int /*<<< orphan*/  action; scalar_t__ ifindex; int /*<<< orphan*/  index; } ;
struct tc_action_net {int dummy; } ;
struct tc_action {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int ACT_P_CREATED ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
#define  TCA_EGRESS_MIRROR 131 
#define  TCA_EGRESS_REDIR 130 
#define  TCA_INGRESS_MIRROR 129 
#define  TCA_INGRESS_REDIR 128 
 int /*<<< orphan*/  TCA_MIRRED_MAX ; 
 size_t TCA_MIRRED_PARMS ; 
 int /*<<< orphan*/  act_mirred_ops ; 
 struct net_device* dev_get_by_index (struct net*,scalar_t__) ; 
 int dev_is_mac_header_xmit (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mirred_list ; 
 int /*<<< orphan*/  mirred_list_lock ; 
 int /*<<< orphan*/  mirred_net_id ; 
 int /*<<< orphan*/  mirred_policy ; 
 struct tc_action_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 struct tc_mirred* nla_data (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  rcu_swap_protected (int /*<<< orphan*/ ,struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int tcf_action_check_ctrlact (int /*<<< orphan*/ ,struct tcf_proto*,struct tcf_chain**,struct netlink_ext_ack*) ; 
 struct tcf_chain* tcf_action_set_ctrlact (struct tc_action*,int /*<<< orphan*/ ,struct tcf_chain*) ; 
 int /*<<< orphan*/  tcf_chain_put_by_act (struct tcf_chain*) ; 
 int tcf_idr_check_alloc (struct tc_action_net*,int /*<<< orphan*/ *,struct tc_action**,int) ; 
 int /*<<< orphan*/  tcf_idr_cleanup (struct tc_action_net*,int /*<<< orphan*/ ) ; 
 int tcf_idr_create (struct tc_action_net*,int /*<<< orphan*/ ,struct nlattr*,struct tc_action**,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  tcf_idr_insert (struct tc_action_net*,struct tc_action*) ; 
 int /*<<< orphan*/  tcf_idr_release (struct tc_action*,int) ; 
 struct tcf_mirred* to_mirred (struct tc_action*) ; 

__attribute__((used)) static int tcf_mirred_init(struct net *net, struct nlattr *nla,
			   struct nlattr *est, struct tc_action **a,
			   int ovr, int bind, bool rtnl_held,
			   struct tcf_proto *tp,
			   struct netlink_ext_ack *extack)
{
	struct tc_action_net *tn = net_generic(net, mirred_net_id);
	struct nlattr *tb[TCA_MIRRED_MAX + 1];
	struct tcf_chain *goto_ch = NULL;
	bool mac_header_xmit = false;
	struct tc_mirred *parm;
	struct tcf_mirred *m;
	struct net_device *dev;
	bool exists = false;
	int ret, err;
	u32 index;

	if (!nla) {
		NL_SET_ERR_MSG_MOD(extack, "Mirred requires attributes to be passed");
		return -EINVAL;
	}
	ret = nla_parse_nested_deprecated(tb, TCA_MIRRED_MAX, nla,
					  mirred_policy, extack);
	if (ret < 0)
		return ret;
	if (!tb[TCA_MIRRED_PARMS]) {
		NL_SET_ERR_MSG_MOD(extack, "Missing required mirred parameters");
		return -EINVAL;
	}
	parm = nla_data(tb[TCA_MIRRED_PARMS]);
	index = parm->index;
	err = tcf_idr_check_alloc(tn, &index, a, bind);
	if (err < 0)
		return err;
	exists = err;
	if (exists && bind)
		return 0;

	switch (parm->eaction) {
	case TCA_EGRESS_MIRROR:
	case TCA_EGRESS_REDIR:
	case TCA_INGRESS_REDIR:
	case TCA_INGRESS_MIRROR:
		break;
	default:
		if (exists)
			tcf_idr_release(*a, bind);
		else
			tcf_idr_cleanup(tn, index);
		NL_SET_ERR_MSG_MOD(extack, "Unknown mirred option");
		return -EINVAL;
	}

	if (!exists) {
		if (!parm->ifindex) {
			tcf_idr_cleanup(tn, index);
			NL_SET_ERR_MSG_MOD(extack, "Specified device does not exist");
			return -EINVAL;
		}
		ret = tcf_idr_create(tn, index, est, a,
				     &act_mirred_ops, bind, true);
		if (ret) {
			tcf_idr_cleanup(tn, index);
			return ret;
		}
		ret = ACT_P_CREATED;
	} else if (!ovr) {
		tcf_idr_release(*a, bind);
		return -EEXIST;
	}

	m = to_mirred(*a);
	if (ret == ACT_P_CREATED)
		INIT_LIST_HEAD(&m->tcfm_list);

	err = tcf_action_check_ctrlact(parm->action, tp, &goto_ch, extack);
	if (err < 0)
		goto release_idr;

	spin_lock_bh(&m->tcf_lock);

	if (parm->ifindex) {
		dev = dev_get_by_index(net, parm->ifindex);
		if (!dev) {
			spin_unlock_bh(&m->tcf_lock);
			err = -ENODEV;
			goto put_chain;
		}
		mac_header_xmit = dev_is_mac_header_xmit(dev);
		rcu_swap_protected(m->tcfm_dev, dev,
				   lockdep_is_held(&m->tcf_lock));
		if (dev)
			dev_put(dev);
		m->tcfm_mac_header_xmit = mac_header_xmit;
	}
	goto_ch = tcf_action_set_ctrlact(*a, parm->action, goto_ch);
	m->tcfm_eaction = parm->eaction;
	spin_unlock_bh(&m->tcf_lock);
	if (goto_ch)
		tcf_chain_put_by_act(goto_ch);

	if (ret == ACT_P_CREATED) {
		spin_lock(&mirred_list_lock);
		list_add(&m->tcfm_list, &mirred_list);
		spin_unlock(&mirred_list_lock);

		tcf_idr_insert(tn, *a);
	}

	return ret;
put_chain:
	if (goto_ch)
		tcf_chain_put_by_act(goto_ch);
release_idr:
	tcf_idr_release(*a, bind);
	return err;
}