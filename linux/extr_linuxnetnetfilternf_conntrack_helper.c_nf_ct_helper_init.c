#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_6__ {int /*<<< orphan*/  all; } ;
struct TYPE_7__ {TYPE_2__ u; scalar_t__ l3num; } ;
struct TYPE_5__ {scalar_t__ protonum; } ;
struct TYPE_8__ {TYPE_3__ src; TYPE_1__ dst; } ;
struct nf_conntrack_helper {int expect_class_max; int (* help ) (struct sk_buff*,unsigned int,struct nf_conn*,int) ;int (* from_nlattr ) (struct nlattr*,struct nf_conn*) ;int /*<<< orphan*/  name; struct module* me; struct nf_conntrack_expect_policy const* expect_policy; TYPE_4__ tuple; } ;
struct nf_conntrack_expect_policy {int dummy; } ;
struct module {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  htons (scalar_t__) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char const*,...) ; 

void nf_ct_helper_init(struct nf_conntrack_helper *helper,
		       u16 l3num, u16 protonum, const char *name,
		       u16 default_port, u16 spec_port, u32 id,
		       const struct nf_conntrack_expect_policy *exp_pol,
		       u32 expect_class_max,
		       int (*help)(struct sk_buff *skb, unsigned int protoff,
				   struct nf_conn *ct,
				   enum ip_conntrack_info ctinfo),
		       int (*from_nlattr)(struct nlattr *attr,
					  struct nf_conn *ct),
		       struct module *module)
{
	helper->tuple.src.l3num = l3num;
	helper->tuple.dst.protonum = protonum;
	helper->tuple.src.u.all = htons(spec_port);
	helper->expect_policy = exp_pol;
	helper->expect_class_max = expect_class_max;
	helper->help = help;
	helper->from_nlattr = from_nlattr;
	helper->me = module;

	if (spec_port == default_port)
		snprintf(helper->name, sizeof(helper->name), "%s", name);
	else
		snprintf(helper->name, sizeof(helper->name), "%s-%u", name, id);
}