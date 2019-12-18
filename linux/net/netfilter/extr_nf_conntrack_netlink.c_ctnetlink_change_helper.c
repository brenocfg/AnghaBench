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
struct nlattr {int dummy; } ;
struct nf_conntrack_helper {char* name; int /*<<< orphan*/  (* from_nlattr ) (struct nlattr*,struct nf_conn*) ;} ;
struct nf_conn_help {struct nf_conntrack_helper* helper; } ;
struct nf_conn {scalar_t__ master; } ;

/* Variables and functions */
 size_t CTA_HELP ; 
 int EBUSY ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (struct nf_conntrack_helper*,int /*<<< orphan*/ *) ; 
 struct nf_conntrack_helper* __nf_conntrack_helper_find (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ctnetlink_parse_help (struct nlattr const* const,char**,struct nlattr**) ; 
 int /*<<< orphan*/  nf_ct_l3num (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_protonum (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_remove_expectations (struct nf_conn*) ; 
 struct nf_conn_help* nfct_help (struct nf_conn*) ; 
 struct nf_conntrack_helper* rcu_dereference (struct nf_conntrack_helper*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  stub1 (struct nlattr*,struct nf_conn*) ; 

__attribute__((used)) static int ctnetlink_change_helper(struct nf_conn *ct,
				   const struct nlattr * const cda[])
{
	struct nf_conntrack_helper *helper;
	struct nf_conn_help *help = nfct_help(ct);
	char *helpname = NULL;
	struct nlattr *helpinfo = NULL;
	int err;

	err = ctnetlink_parse_help(cda[CTA_HELP], &helpname, &helpinfo);
	if (err < 0)
		return err;

	/* don't change helper of sibling connections */
	if (ct->master) {
		/* If we try to change the helper to the same thing twice,
		 * treat the second attempt as a no-op instead of returning
		 * an error.
		 */
		err = -EBUSY;
		if (help) {
			rcu_read_lock();
			helper = rcu_dereference(help->helper);
			if (helper && !strcmp(helper->name, helpname))
				err = 0;
			rcu_read_unlock();
		}

		return err;
	}

	if (!strcmp(helpname, "")) {
		if (help && help->helper) {
			/* we had a helper before ... */
			nf_ct_remove_expectations(ct);
			RCU_INIT_POINTER(help->helper, NULL);
		}

		return 0;
	}

	rcu_read_lock();
	helper = __nf_conntrack_helper_find(helpname, nf_ct_l3num(ct),
					    nf_ct_protonum(ct));
	if (helper == NULL) {
		rcu_read_unlock();
		return -EOPNOTSUPP;
	}

	if (help) {
		if (help->helper == helper) {
			/* update private helper data if allowed. */
			if (helper->from_nlattr)
				helper->from_nlattr(helpinfo, ct);
			err = 0;
		} else
			err = -EBUSY;
	} else {
		/* we cannot set a helper for an existing conntrack */
		err = -EOPNOTSUPP;
	}

	rcu_read_unlock();
	return err;
}