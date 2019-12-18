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
struct nf_conntrack_helper {scalar_t__ help; } ;
struct nf_conn_help {struct nf_conntrack_helper* helper; } ;
struct nf_conn {int /*<<< orphan*/  status; } ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IPS_HELPER_BIT ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (struct nf_conntrack_helper*,int /*<<< orphan*/ *) ; 
 struct nf_conn_help* nf_ct_helper_ext_add (struct nf_conn*,int /*<<< orphan*/ ) ; 
 struct nf_conntrack_helper* nf_ct_lookup_helper (struct nf_conn*,struct net*) ; 
 struct net* nf_ct_net (struct nf_conn*) ; 
 struct nf_conn_help* nfct_help (struct nf_conn*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct nf_conntrack_helper*,struct nf_conntrack_helper*) ; 
 struct nf_conntrack_helper* rcu_dereference (struct nf_conntrack_helper*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int __nf_ct_try_assign_helper(struct nf_conn *ct, struct nf_conn *tmpl,
			      gfp_t flags)
{
	struct nf_conntrack_helper *helper = NULL;
	struct nf_conn_help *help;
	struct net *net = nf_ct_net(ct);

	/* We already got a helper explicitly attached. The function
	 * nf_conntrack_alter_reply - in case NAT is in use - asks for looking
	 * the helper up again. Since now the user is in full control of
	 * making consistent helper configurations, skip this automatic
	 * re-lookup, otherwise we'll lose the helper.
	 */
	if (test_bit(IPS_HELPER_BIT, &ct->status))
		return 0;

	if (tmpl != NULL) {
		help = nfct_help(tmpl);
		if (help != NULL) {
			helper = help->helper;
			set_bit(IPS_HELPER_BIT, &ct->status);
		}
	}

	help = nfct_help(ct);

	if (helper == NULL) {
		helper = nf_ct_lookup_helper(ct, net);
		if (helper == NULL) {
			if (help)
				RCU_INIT_POINTER(help->helper, NULL);
			return 0;
		}
	}

	if (help == NULL) {
		help = nf_ct_helper_ext_add(ct, flags);
		if (help == NULL)
			return -ENOMEM;
	} else {
		/* We only allow helper re-assignment of the same sort since
		 * we cannot reallocate the helper extension area.
		 */
		struct nf_conntrack_helper *tmp = rcu_dereference(help->helper);

		if (tmp && tmp->help != helper->help) {
			RCU_INIT_POINTER(help->helper, NULL);
			return 0;
		}
	}

	rcu_assign_pointer(help->helper, helper);

	return 0;
}