#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct tcmsg {int tcm_handle; int /*<<< orphan*/  tcm_info; } ;
struct TYPE_8__ {int itf; int /*<<< orphan*/  vci; int /*<<< orphan*/  vpi; } ;
struct sockaddr_atmpvc {TYPE_3__ sap_addr; int /*<<< orphan*/  sap_family; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct atm_qdisc_data {int dummy; } ;
struct TYPE_10__ {int classid; } ;
struct atm_flow_data {int hdr_len; TYPE_5__ common; scalar_t__ excess; TYPE_4__* vcc; struct sockaddr_atmpvc* hdr; TYPE_1__* q; int /*<<< orphan*/  list; } ;
struct Qdisc {int dummy; } ;
typedef  int /*<<< orphan*/  pvc ;
struct TYPE_9__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  vci; int /*<<< orphan*/  vpi; TYPE_2__* dev; } ;
struct TYPE_7__ {int number; } ;
struct TYPE_6__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_ATMPVC ; 
 int ATM_VF2VS (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  TCA_ATM_ADDR ; 
 int /*<<< orphan*/  TCA_ATM_EXCESS ; 
 int /*<<< orphan*/  TCA_ATM_HDR ; 
 int /*<<< orphan*/  TCA_ATM_STATE ; 
 int /*<<< orphan*/  TCA_OPTIONS ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct sockaddr_atmpvc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct sockaddr_atmpvc*) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,struct Qdisc*,struct atm_qdisc_data*,struct atm_flow_data*,struct sk_buff*,struct tcmsg*) ; 
 struct atm_qdisc_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static int atm_tc_dump_class(struct Qdisc *sch, unsigned long cl,
			     struct sk_buff *skb, struct tcmsg *tcm)
{
	struct atm_qdisc_data *p = qdisc_priv(sch);
	struct atm_flow_data *flow = (struct atm_flow_data *)cl;
	struct nlattr *nest;

	pr_debug("atm_tc_dump_class(sch %p,[qdisc %p],flow %p,skb %p,tcm %p)\n",
		sch, p, flow, skb, tcm);
	if (list_empty(&flow->list))
		return -EINVAL;
	tcm->tcm_handle = flow->common.classid;
	tcm->tcm_info = flow->q->handle;

	nest = nla_nest_start_noflag(skb, TCA_OPTIONS);
	if (nest == NULL)
		goto nla_put_failure;

	if (nla_put(skb, TCA_ATM_HDR, flow->hdr_len, flow->hdr))
		goto nla_put_failure;
	if (flow->vcc) {
		struct sockaddr_atmpvc pvc;
		int state;

		memset(&pvc, 0, sizeof(pvc));
		pvc.sap_family = AF_ATMPVC;
		pvc.sap_addr.itf = flow->vcc->dev ? flow->vcc->dev->number : -1;
		pvc.sap_addr.vpi = flow->vcc->vpi;
		pvc.sap_addr.vci = flow->vcc->vci;
		if (nla_put(skb, TCA_ATM_ADDR, sizeof(pvc), &pvc))
			goto nla_put_failure;
		state = ATM_VF2VS(flow->vcc->flags);
		if (nla_put_u32(skb, TCA_ATM_STATE, state))
			goto nla_put_failure;
	}
	if (flow->excess) {
		if (nla_put_u32(skb, TCA_ATM_EXCESS, flow->common.classid))
			goto nla_put_failure;
	} else {
		if (nla_put_u32(skb, TCA_ATM_EXCESS, 0))
			goto nla_put_failure;
	}
	return nla_nest_end(skb, nest);

nla_put_failure:
	nla_nest_cancel(skb, nest);
	return -1;
}