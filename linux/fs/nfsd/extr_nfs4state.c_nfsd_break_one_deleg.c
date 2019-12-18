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
struct TYPE_2__ {int /*<<< orphan*/  sc_count; } ;
struct nfs4_delegation {int /*<<< orphan*/  dl_recall; TYPE_1__ dl_stid; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfsd4_run_cb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfsd_break_one_deleg(struct nfs4_delegation *dp)
{
	/*
	 * We're assuming the state code never drops its reference
	 * without first removing the lease.  Since we're in this lease
	 * callback (and since the lease code is serialized by the
	 * i_lock) we know the server hasn't removed the lease yet, and
	 * we know it's safe to take a reference.
	 */
	refcount_inc(&dp->dl_stid.sc_count);
	nfsd4_run_cb(&dp->dl_recall);
}