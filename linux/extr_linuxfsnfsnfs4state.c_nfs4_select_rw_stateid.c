#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct rpc_cred {int dummy; } ;
struct nfs_lock_context {int dummy; } ;
struct nfs4_state {int /*<<< orphan*/  inode; } ;
struct TYPE_6__ {scalar_t__ seqid; } ;
typedef  TYPE_1__ nfs4_stateid ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 int EIO ; 
 int ENOENT ; 
 int /*<<< orphan*/  NFS_CAP_STATEID_NFSV41 ; 
 scalar_t__ nfs4_copy_delegation_stateid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,struct rpc_cred**) ; 
 int nfs4_copy_lock_stateid (TYPE_1__*,struct nfs4_state*,struct nfs_lock_context const*) ; 
 int /*<<< orphan*/  nfs4_copy_open_stateid (TYPE_1__*,struct nfs4_state*) ; 
 int /*<<< orphan*/  nfs4_valid_open_stateid (struct nfs4_state*) ; 
 scalar_t__ nfs_server_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int nfs4_select_rw_stateid(struct nfs4_state *state,
		fmode_t fmode, const struct nfs_lock_context *l_ctx,
		nfs4_stateid *dst, struct rpc_cred **cred)
{
	int ret;

	if (!nfs4_valid_open_stateid(state))
		return -EIO;
	if (cred != NULL)
		*cred = NULL;
	ret = nfs4_copy_lock_stateid(dst, state, l_ctx);
	if (ret == -EIO)
		/* A lost lock - don't even consider delegations */
		goto out;
	/* returns true if delegation stateid found and copied */
	if (nfs4_copy_delegation_stateid(state->inode, fmode, dst, cred)) {
		ret = 0;
		goto out;
	}
	if (ret != -ENOENT)
		/* nfs4_copy_delegation_stateid() didn't over-write
		 * dst, so it still has the lock stateid which we now
		 * choose to use.
		 */
		goto out;
	nfs4_copy_open_stateid(dst, state);
	ret = 0;
out:
	if (nfs_server_capable(state->inode, NFS_CAP_STATEID_NFSV41))
		dst->seqid = 0;
	return ret;
}