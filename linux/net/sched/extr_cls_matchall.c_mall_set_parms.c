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
struct TYPE_2__ {int /*<<< orphan*/  classid; } ;
struct cls_mall_head {TYPE_1__ res; int /*<<< orphan*/  exts; } ;

/* Variables and functions */
 size_t TCA_MATCHALL_CLASSID ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  tcf_bind_filter (struct tcf_proto*,TYPE_1__*,unsigned long) ; 
 int tcf_exts_validate (struct net*,struct tcf_proto*,struct nlattr**,struct nlattr*,int /*<<< orphan*/ *,int,int,struct netlink_ext_ack*) ; 

__attribute__((used)) static int mall_set_parms(struct net *net, struct tcf_proto *tp,
			  struct cls_mall_head *head,
			  unsigned long base, struct nlattr **tb,
			  struct nlattr *est, bool ovr,
			  struct netlink_ext_ack *extack)
{
	int err;

	err = tcf_exts_validate(net, tp, tb, est, &head->exts, ovr, true,
				extack);
	if (err < 0)
		return err;

	if (tb[TCA_MATCHALL_CLASSID]) {
		head->res.classid = nla_get_u32(tb[TCA_MATCHALL_CLASSID]);
		tcf_bind_filter(tp, &head->res, base);
	}
	return 0;
}