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
struct nf_conntrack_helper {int dummy; } ;
struct nf_conntrack_expect {struct nf_conntrack_helper const* helper; int /*<<< orphan*/  master; } ;
struct nf_conn_help {int /*<<< orphan*/  helper; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_conntrack_expect_lock ; 
 struct nf_conn_help* nfct_help (int /*<<< orphan*/ ) ; 
 struct nf_conntrack_helper* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool expect_iter_me(struct nf_conntrack_expect *exp, void *data)
{
	struct nf_conn_help *help = nfct_help(exp->master);
	const struct nf_conntrack_helper *me = data;
	const struct nf_conntrack_helper *this;

	if (exp->helper == me)
		return true;

	this = rcu_dereference_protected(help->helper,
					 lockdep_is_held(&nf_conntrack_expect_lock));
	return this == me;
}