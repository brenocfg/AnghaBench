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
struct nf_conntrack {int /*<<< orphan*/  use; } ;
struct nf_conn {scalar_t__ master; } ;

/* Variables and functions */
 scalar_t__ IPPROTO_GRE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_gre_conntrack (struct nf_conn*) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  nf_conntrack_free (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_del_from_dying_or_unconfirmed_list (struct nf_conn*) ; 
 int nf_ct_is_template (struct nf_conn*) ; 
 scalar_t__ nf_ct_protonum (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_put (scalar_t__) ; 
 int /*<<< orphan*/  nf_ct_remove_expectations (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_tmpl_free (struct nf_conn*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct nf_conn*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
destroy_conntrack(struct nf_conntrack *nfct)
{
	struct nf_conn *ct = (struct nf_conn *)nfct;

	pr_debug("destroy_conntrack(%p)\n", ct);
	WARN_ON(atomic_read(&nfct->use) != 0);

	if (unlikely(nf_ct_is_template(ct))) {
		nf_ct_tmpl_free(ct);
		return;
	}

	if (unlikely(nf_ct_protonum(ct) == IPPROTO_GRE))
		destroy_gre_conntrack(ct);

	local_bh_disable();
	/* Expectations will have been removed in clean_from_lists,
	 * except TFTP can create an expectation on the first packet,
	 * before connection is in the list, so we need to clean here,
	 * too.
	 */
	nf_ct_remove_expectations(ct);

	nf_ct_del_from_dying_or_unconfirmed_list(ct);

	local_bh_enable();

	if (ct->master)
		nf_ct_put(ct->master);

	pr_debug("destroy_conntrack: returning ct=%p to slab\n", ct);
	nf_conntrack_free(ct);
}