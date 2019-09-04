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
struct TYPE_2__ {int /*<<< orphan*/  sc_count; int /*<<< orphan*/  sc_type; struct nfs4_client* sc_client; } ;
struct nfs4_delegation {int /*<<< orphan*/  dl_recall_lru; TYPE_1__ dl_stid; } ;
struct nfs4_client {int /*<<< orphan*/  cl_lock; int /*<<< orphan*/  cl_revoked; scalar_t__ cl_minorversion; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4_REVOKED_DELEG_STID ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  destroy_unhashed_deleg (struct nfs4_delegation*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void revoke_delegation(struct nfs4_delegation *dp)
{
	struct nfs4_client *clp = dp->dl_stid.sc_client;

	WARN_ON(!list_empty(&dp->dl_recall_lru));

	if (clp->cl_minorversion) {
		dp->dl_stid.sc_type = NFS4_REVOKED_DELEG_STID;
		refcount_inc(&dp->dl_stid.sc_count);
		spin_lock(&clp->cl_lock);
		list_add(&dp->dl_recall_lru, &clp->cl_revoked);
		spin_unlock(&clp->cl_lock);
	}
	destroy_unhashed_deleg(dp);
}