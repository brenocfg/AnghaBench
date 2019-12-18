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
struct nf_conn_help {int /*<<< orphan*/  helper; } ;
struct nf_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPCT_HELPER ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_conntrack_event (int /*<<< orphan*/ ,struct nf_conn*) ; 
 struct nf_conn_help* nfct_help (struct nf_conn*) ; 
 void* rcu_dereference_raw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int unhelp(struct nf_conn *ct, void *me)
{
	struct nf_conn_help *help = nfct_help(ct);

	if (help && rcu_dereference_raw(help->helper) == me) {
		nf_conntrack_event(IPCT_HELPER, ct);
		RCU_INIT_POINTER(help->helper, NULL);
	}

	/* We are not intended to delete this conntrack. */
	return 0;
}