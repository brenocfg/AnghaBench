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
typedef  int /*<<< orphan*/  u32 ;
struct nf_conntrack_expect {size_t class; int /*<<< orphan*/  lnode; int /*<<< orphan*/  hnode; int /*<<< orphan*/  timeout; int /*<<< orphan*/  master; } ;
struct nf_conn_help {int /*<<< orphan*/ * expecting; } ;
struct TYPE_2__ {int /*<<< orphan*/  expect_count; } ;
struct net {TYPE_1__ ct; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPEXP_DESTROY ; 
 int /*<<< orphan*/  NF_CT_STAT_INC (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  expect_delete ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 struct net* nf_ct_exp_net (struct nf_conntrack_expect*) ; 
 int /*<<< orphan*/  nf_ct_expect_event_report (int /*<<< orphan*/ ,struct nf_conntrack_expect*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nf_ct_expect_put (struct nf_conntrack_expect*) ; 
 struct nf_conn_help* nfct_help (int /*<<< orphan*/ ) ; 
 int timer_pending (int /*<<< orphan*/ *) ; 

void nf_ct_unlink_expect_report(struct nf_conntrack_expect *exp,
				u32 portid, int report)
{
	struct nf_conn_help *master_help = nfct_help(exp->master);
	struct net *net = nf_ct_exp_net(exp);

	WARN_ON(!master_help);
	WARN_ON(timer_pending(&exp->timeout));

	hlist_del_rcu(&exp->hnode);
	net->ct.expect_count--;

	hlist_del_rcu(&exp->lnode);
	master_help->expecting[exp->class]--;

	nf_ct_expect_event_report(IPEXP_DESTROY, exp, portid, report);
	nf_ct_expect_put(exp);

	NF_CT_STAT_INC(net, expect_delete);
}