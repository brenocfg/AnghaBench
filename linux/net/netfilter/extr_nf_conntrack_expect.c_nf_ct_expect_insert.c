#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nf_conntrack_helper {TYPE_1__* expect_policy; } ;
struct TYPE_7__ {scalar_t__ expires; } ;
struct nf_conntrack_expect {size_t class; int /*<<< orphan*/  hnode; int /*<<< orphan*/  lnode; TYPE_3__ timeout; int /*<<< orphan*/  use; int /*<<< orphan*/  tuple; int /*<<< orphan*/  master; } ;
struct nf_conn_help {int /*<<< orphan*/ * expecting; int /*<<< orphan*/  expectations; int /*<<< orphan*/  helper; } ;
struct TYPE_6__ {int /*<<< orphan*/  expect_count; } ;
struct net {TYPE_2__ ct; } ;
struct TYPE_5__ {int timeout; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  NF_CT_STAT_INC (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  expect_create ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_conntrack_expect_lock ; 
 struct net* nf_ct_exp_net (struct nf_conntrack_expect*) ; 
 unsigned int nf_ct_expect_dst_hash (struct net*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nf_ct_expect_hash ; 
 int /*<<< orphan*/  nf_ct_expectation_timed_out ; 
 struct nf_conn_help* nfct_help (int /*<<< orphan*/ ) ; 
 struct nf_conntrack_helper* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nf_ct_expect_insert(struct nf_conntrack_expect *exp)
{
	struct nf_conn_help *master_help = nfct_help(exp->master);
	struct nf_conntrack_helper *helper;
	struct net *net = nf_ct_exp_net(exp);
	unsigned int h = nf_ct_expect_dst_hash(net, &exp->tuple);

	/* two references : one for hash insert, one for the timer */
	refcount_add(2, &exp->use);

	timer_setup(&exp->timeout, nf_ct_expectation_timed_out, 0);
	helper = rcu_dereference_protected(master_help->helper,
					   lockdep_is_held(&nf_conntrack_expect_lock));
	if (helper) {
		exp->timeout.expires = jiffies +
			helper->expect_policy[exp->class].timeout * HZ;
	}
	add_timer(&exp->timeout);

	hlist_add_head_rcu(&exp->lnode, &master_help->expectations);
	master_help->expecting[exp->class]++;

	hlist_add_head_rcu(&exp->hnode, &nf_ct_expect_hash[h]);
	net->ct.expect_count++;

	NF_CT_STAT_INC(net, expect_create);
}