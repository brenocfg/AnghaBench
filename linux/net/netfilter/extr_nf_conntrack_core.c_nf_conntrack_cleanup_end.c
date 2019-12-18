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
struct TYPE_2__ {int /*<<< orphan*/  dwork; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 TYPE_1__ conntrack_gc_work ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_conntrack_acct_fini () ; 
 int /*<<< orphan*/  nf_conntrack_cachep ; 
 int /*<<< orphan*/  nf_conntrack_ecache_fini () ; 
 int /*<<< orphan*/  nf_conntrack_expect_fini () ; 
 int /*<<< orphan*/  nf_conntrack_hash ; 
 int /*<<< orphan*/  nf_conntrack_helper_fini () ; 
 int /*<<< orphan*/  nf_conntrack_labels_fini () ; 
 int /*<<< orphan*/  nf_conntrack_proto_fini () ; 
 int /*<<< orphan*/  nf_conntrack_seqadj_fini () ; 
 int /*<<< orphan*/  nf_conntrack_timeout_fini () ; 
 int /*<<< orphan*/  nf_conntrack_tstamp_fini () ; 
 int /*<<< orphan*/  nf_ct_hook ; 

void nf_conntrack_cleanup_end(void)
{
	RCU_INIT_POINTER(nf_ct_hook, NULL);
	cancel_delayed_work_sync(&conntrack_gc_work.dwork);
	kvfree(nf_conntrack_hash);

	nf_conntrack_proto_fini();
	nf_conntrack_seqadj_fini();
	nf_conntrack_labels_fini();
	nf_conntrack_helper_fini();
	nf_conntrack_timeout_fini();
	nf_conntrack_ecache_fini();
	nf_conntrack_tstamp_fini();
	nf_conntrack_acct_fini();
	nf_conntrack_expect_fini();

	kmem_cache_destroy(nf_conntrack_cachep);
}