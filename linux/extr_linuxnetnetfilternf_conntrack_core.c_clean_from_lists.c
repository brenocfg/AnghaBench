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
struct nf_conn {TYPE_1__* tuplehash; } ;
struct TYPE_2__ {int /*<<< orphan*/  hnnode; } ;

/* Variables and functions */
 size_t IP_CT_DIR_ORIGINAL ; 
 size_t IP_CT_DIR_REPLY ; 
 int /*<<< orphan*/  hlist_nulls_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_ct_remove_expectations (struct nf_conn*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct nf_conn*) ; 

__attribute__((used)) static void
clean_from_lists(struct nf_conn *ct)
{
	pr_debug("clean_from_lists(%p)\n", ct);
	hlist_nulls_del_rcu(&ct->tuplehash[IP_CT_DIR_ORIGINAL].hnnode);
	hlist_nulls_del_rcu(&ct->tuplehash[IP_CT_DIR_REPLY].hnnode);

	/* Destroy all pending expectations */
	nf_ct_remove_expectations(ct);
}