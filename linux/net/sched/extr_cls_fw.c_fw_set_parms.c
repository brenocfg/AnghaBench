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
typedef  int u32 ;
struct tcf_proto {int /*<<< orphan*/  root; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;
struct fw_head {int mask; } ;
struct TYPE_2__ {void* classid; } ;
struct fw_filter {int ifindex; TYPE_1__ res; int /*<<< orphan*/  exts; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t TCA_FW_CLASSID ; 
 size_t TCA_FW_INDEV ; 
 size_t TCA_FW_MASK ; 
 size_t TCA_RATE ; 
 void* nla_get_u32 (struct nlattr*) ; 
 struct fw_head* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_bind_filter (struct tcf_proto*,TYPE_1__*,unsigned long) ; 
 int tcf_change_indev (struct net*,struct nlattr*,struct netlink_ext_ack*) ; 
 int tcf_exts_validate (struct net*,struct tcf_proto*,struct nlattr**,struct nlattr*,int /*<<< orphan*/ *,int,int,struct netlink_ext_ack*) ; 

__attribute__((used)) static int fw_set_parms(struct net *net, struct tcf_proto *tp,
			struct fw_filter *f, struct nlattr **tb,
			struct nlattr **tca, unsigned long base, bool ovr,
			struct netlink_ext_ack *extack)
{
	struct fw_head *head = rtnl_dereference(tp->root);
	u32 mask;
	int err;

	err = tcf_exts_validate(net, tp, tb, tca[TCA_RATE], &f->exts, ovr,
				true, extack);
	if (err < 0)
		return err;

	if (tb[TCA_FW_CLASSID]) {
		f->res.classid = nla_get_u32(tb[TCA_FW_CLASSID]);
		tcf_bind_filter(tp, &f->res, base);
	}

	if (tb[TCA_FW_INDEV]) {
		int ret;
		ret = tcf_change_indev(net, tb[TCA_FW_INDEV], extack);
		if (ret < 0)
			return ret;
		f->ifindex = ret;
	}

	err = -EINVAL;
	if (tb[TCA_FW_MASK]) {
		mask = nla_get_u32(tb[TCA_FW_MASK]);
		if (mask != head->mask)
			return err;
	} else if (head->mask != 0xFFFFFFFF)
		return err;

	return 0;
}