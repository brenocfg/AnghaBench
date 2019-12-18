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
struct tcf_proto {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;
struct fl_flow_tmplt {int dummy; } ;
struct fl_flow_mask {int /*<<< orphan*/  key; } ;
struct TYPE_2__ {int /*<<< orphan*/  classid; } ;
struct cls_fl_filter {int /*<<< orphan*/  key; int /*<<< orphan*/  mkey; TYPE_1__ res; int /*<<< orphan*/  exts; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 size_t TCA_FLOWER_CLASSID ; 
 int /*<<< orphan*/  fl_mask_fits_tmplt (struct fl_flow_tmplt*,struct fl_flow_mask*) ; 
 int /*<<< orphan*/  fl_mask_update_range (struct fl_flow_mask*) ; 
 int fl_set_key (struct net*,struct nlattr**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  fl_set_masked_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct fl_flow_mask*) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  tcf_bind_filter (struct tcf_proto*,TYPE_1__*,unsigned long) ; 
 int tcf_exts_validate (struct net*,struct tcf_proto*,struct nlattr**,struct nlattr*,int /*<<< orphan*/ *,int,int,struct netlink_ext_ack*) ; 

__attribute__((used)) static int fl_set_parms(struct net *net, struct tcf_proto *tp,
			struct cls_fl_filter *f, struct fl_flow_mask *mask,
			unsigned long base, struct nlattr **tb,
			struct nlattr *est, bool ovr,
			struct fl_flow_tmplt *tmplt, bool rtnl_held,
			struct netlink_ext_ack *extack)
{
	int err;

	err = tcf_exts_validate(net, tp, tb, est, &f->exts, ovr, rtnl_held,
				extack);
	if (err < 0)
		return err;

	if (tb[TCA_FLOWER_CLASSID]) {
		f->res.classid = nla_get_u32(tb[TCA_FLOWER_CLASSID]);
		if (!rtnl_held)
			rtnl_lock();
		tcf_bind_filter(tp, &f->res, base);
		if (!rtnl_held)
			rtnl_unlock();
	}

	err = fl_set_key(net, tb, &f->key, &mask->key, extack);
	if (err)
		return err;

	fl_mask_update_range(mask);
	fl_set_masked_key(&f->mkey, &f->key, mask);

	if (!fl_mask_fits_tmplt(tmplt, mask)) {
		NL_SET_ERR_MSG_MOD(extack, "Mask does not fit the template");
		return -EINVAL;
	}

	return 0;
}