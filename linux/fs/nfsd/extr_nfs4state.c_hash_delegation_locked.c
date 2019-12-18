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
struct nfs4_file {int /*<<< orphan*/  fi_delegations; int /*<<< orphan*/  fi_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  sc_type; int /*<<< orphan*/  sc_count; struct nfs4_client* sc_client; } ;
struct nfs4_delegation {int /*<<< orphan*/  dl_perclnt; int /*<<< orphan*/  dl_perfile; TYPE_1__ dl_stid; } ;
struct nfs4_client {int /*<<< orphan*/  cl_delegations; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  NFS4_DELEG_STID ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 scalar_t__ nfs4_delegation_exists (struct nfs4_client*,struct nfs4_file*) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  state_lock ; 

__attribute__((used)) static int
hash_delegation_locked(struct nfs4_delegation *dp, struct nfs4_file *fp)
{
	struct nfs4_client *clp = dp->dl_stid.sc_client;

	lockdep_assert_held(&state_lock);
	lockdep_assert_held(&fp->fi_lock);

	if (nfs4_delegation_exists(clp, fp))
		return -EAGAIN;
	refcount_inc(&dp->dl_stid.sc_count);
	dp->dl_stid.sc_type = NFS4_DELEG_STID;
	list_add(&dp->dl_perfile, &fp->fi_delegations);
	list_add(&dp->dl_perclnt, &clp->cl_delegations);
	return 0;
}