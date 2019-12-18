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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct tcf_proto {int dummy; } ;
struct tcf_ife_params {int flags; int /*<<< orphan*/  eth_type; int /*<<< orphan*/  eth_src; int /*<<< orphan*/  eth_dst; } ;
struct tcf_ife_info {int /*<<< orphan*/  tcf_lock; int /*<<< orphan*/  params; int /*<<< orphan*/  metalist; } ;
struct tcf_chain {int dummy; } ;
struct tc_ife {int flags; int /*<<< orphan*/  action; int /*<<< orphan*/  index; } ;
struct tc_action_net {int dummy; } ;
struct tc_action {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int ACT_P_CREATED ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_P_IFE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IFE_ENCODE ; 
 int /*<<< orphan*/  IFE_META_MAX ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 size_t TCA_IFE_DMAC ; 
 int /*<<< orphan*/  TCA_IFE_MAX ; 
 size_t TCA_IFE_METALST ; 
 size_t TCA_IFE_PARMS ; 
 size_t TCA_IFE_SMAC ; 
 size_t TCA_IFE_TYPE ; 
 int /*<<< orphan*/  act_ife_ops ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ife_net_id ; 
 int /*<<< orphan*/ * ife_policy ; 
 int /*<<< orphan*/  kfree (struct tcf_ife_params*) ; 
 int /*<<< orphan*/  kfree_rcu (struct tcf_ife_params*,int /*<<< orphan*/ ) ; 
 struct tcf_ife_params* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct tc_action_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 void* nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u16 (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int populate_metalist (struct tcf_ife_info*,struct nlattr**,int,int) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  rcu_swap_protected (int /*<<< orphan*/ ,struct tcf_ife_params*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int tcf_action_check_ctrlact (int /*<<< orphan*/ ,struct tcf_proto*,struct tcf_chain**,struct netlink_ext_ack*) ; 
 struct tcf_chain* tcf_action_set_ctrlact (struct tc_action*,int /*<<< orphan*/ ,struct tcf_chain*) ; 
 int /*<<< orphan*/  tcf_chain_put_by_act (struct tcf_chain*) ; 
 int tcf_idr_check_alloc (struct tc_action_net*,int /*<<< orphan*/ *,struct tc_action**,int) ; 
 int /*<<< orphan*/  tcf_idr_cleanup (struct tc_action_net*,int /*<<< orphan*/ ) ; 
 int tcf_idr_create (struct tc_action_net*,int /*<<< orphan*/ ,struct nlattr*,struct tc_action**,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  tcf_idr_insert (struct tc_action_net*,struct tc_action*) ; 
 int /*<<< orphan*/  tcf_idr_release (struct tc_action*,int) ; 
 struct tcf_ife_info* to_ife (struct tc_action*) ; 
 int use_all_metadata (struct tcf_ife_info*,int) ; 

__attribute__((used)) static int tcf_ife_init(struct net *net, struct nlattr *nla,
			struct nlattr *est, struct tc_action **a,
			int ovr, int bind, bool rtnl_held,
			struct tcf_proto *tp, struct netlink_ext_ack *extack)
{
	struct tc_action_net *tn = net_generic(net, ife_net_id);
	struct nlattr *tb[TCA_IFE_MAX + 1];
	struct nlattr *tb2[IFE_META_MAX + 1];
	struct tcf_chain *goto_ch = NULL;
	struct tcf_ife_params *p;
	struct tcf_ife_info *ife;
	u16 ife_type = ETH_P_IFE;
	struct tc_ife *parm;
	u8 *daddr = NULL;
	u8 *saddr = NULL;
	bool exists = false;
	int ret = 0;
	u32 index;
	int err;

	if (!nla) {
		NL_SET_ERR_MSG_MOD(extack, "IFE requires attributes to be passed");
		return -EINVAL;
	}

	err = nla_parse_nested_deprecated(tb, TCA_IFE_MAX, nla, ife_policy,
					  NULL);
	if (err < 0)
		return err;

	if (!tb[TCA_IFE_PARMS])
		return -EINVAL;

	parm = nla_data(tb[TCA_IFE_PARMS]);

	/* IFE_DECODE is 0 and indicates the opposite of IFE_ENCODE because
	 * they cannot run as the same time. Check on all other values which
	 * are not supported right now.
	 */
	if (parm->flags & ~IFE_ENCODE)
		return -EINVAL;

	p = kzalloc(sizeof(*p), GFP_KERNEL);
	if (!p)
		return -ENOMEM;

	index = parm->index;
	err = tcf_idr_check_alloc(tn, &index, a, bind);
	if (err < 0) {
		kfree(p);
		return err;
	}
	exists = err;
	if (exists && bind) {
		kfree(p);
		return 0;
	}

	if (!exists) {
		ret = tcf_idr_create(tn, index, est, a, &act_ife_ops,
				     bind, true);
		if (ret) {
			tcf_idr_cleanup(tn, index);
			kfree(p);
			return ret;
		}
		ret = ACT_P_CREATED;
	} else if (!ovr) {
		tcf_idr_release(*a, bind);
		kfree(p);
		return -EEXIST;
	}

	ife = to_ife(*a);
	err = tcf_action_check_ctrlact(parm->action, tp, &goto_ch, extack);
	if (err < 0)
		goto release_idr;

	p->flags = parm->flags;

	if (parm->flags & IFE_ENCODE) {
		if (tb[TCA_IFE_TYPE])
			ife_type = nla_get_u16(tb[TCA_IFE_TYPE]);
		if (tb[TCA_IFE_DMAC])
			daddr = nla_data(tb[TCA_IFE_DMAC]);
		if (tb[TCA_IFE_SMAC])
			saddr = nla_data(tb[TCA_IFE_SMAC]);
	}

	if (parm->flags & IFE_ENCODE) {
		if (daddr)
			ether_addr_copy(p->eth_dst, daddr);
		else
			eth_zero_addr(p->eth_dst);

		if (saddr)
			ether_addr_copy(p->eth_src, saddr);
		else
			eth_zero_addr(p->eth_src);

		p->eth_type = ife_type;
	}


	if (ret == ACT_P_CREATED)
		INIT_LIST_HEAD(&ife->metalist);

	if (tb[TCA_IFE_METALST]) {
		err = nla_parse_nested_deprecated(tb2, IFE_META_MAX,
						  tb[TCA_IFE_METALST], NULL,
						  NULL);
		if (err)
			goto metadata_parse_err;
		err = populate_metalist(ife, tb2, exists, rtnl_held);
		if (err)
			goto metadata_parse_err;

	} else {
		/* if no passed metadata allow list or passed allow-all
		 * then here we process by adding as many supported metadatum
		 * as we can. You better have at least one else we are
		 * going to bail out
		 */
		err = use_all_metadata(ife, exists);
		if (err)
			goto metadata_parse_err;
	}

	if (exists)
		spin_lock_bh(&ife->tcf_lock);
	/* protected by tcf_lock when modifying existing action */
	goto_ch = tcf_action_set_ctrlact(*a, parm->action, goto_ch);
	rcu_swap_protected(ife->params, p, 1);

	if (exists)
		spin_unlock_bh(&ife->tcf_lock);
	if (goto_ch)
		tcf_chain_put_by_act(goto_ch);
	if (p)
		kfree_rcu(p, rcu);

	if (ret == ACT_P_CREATED)
		tcf_idr_insert(tn, *a);

	return ret;
metadata_parse_err:
	if (goto_ch)
		tcf_chain_put_by_act(goto_ch);
release_idr:
	kfree(p);
	tcf_idr_release(*a, bind);
	return err;
}