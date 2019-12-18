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
struct nfs_lock_context {TYPE_1__* open_context; int /*<<< orphan*/  lockowner; } ;
struct nfs4_state {int /*<<< orphan*/  state_lock; int /*<<< orphan*/  flags; } ;
struct nfs4_lock_state {int /*<<< orphan*/  ls_stateid; int /*<<< orphan*/  ls_flags; } ;
typedef  int /*<<< orphan*/  nfs4_stateid ;
typedef  int /*<<< orphan*/  fl_owner_t ;
struct TYPE_2__ {int /*<<< orphan*/  flock_owner; } ;

/* Variables and functions */
 int EIO ; 
 int ENOENT ; 
 int /*<<< orphan*/  LK_STATE_IN_USE ; 
 int /*<<< orphan*/  NFS_LOCK_INITIALIZED ; 
 int /*<<< orphan*/  NFS_LOCK_LOST ; 
 struct nfs4_lock_state* __nfs4_find_lock_state (struct nfs4_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_put_lock_state (struct nfs4_lock_state*) ; 
 int /*<<< orphan*/  nfs4_stateid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfs4_copy_lock_stateid(nfs4_stateid *dst,
		struct nfs4_state *state,
		const struct nfs_lock_context *l_ctx)
{
	struct nfs4_lock_state *lsp;
	fl_owner_t fl_owner, fl_flock_owner;
	int ret = -ENOENT;

	if (l_ctx == NULL)
		goto out;

	if (test_bit(LK_STATE_IN_USE, &state->flags) == 0)
		goto out;

	fl_owner = l_ctx->lockowner;
	fl_flock_owner = l_ctx->open_context->flock_owner;

	spin_lock(&state->state_lock);
	lsp = __nfs4_find_lock_state(state, fl_owner, fl_flock_owner);
	if (lsp && test_bit(NFS_LOCK_LOST, &lsp->ls_flags))
		ret = -EIO;
	else if (lsp != NULL && test_bit(NFS_LOCK_INITIALIZED, &lsp->ls_flags) != 0) {
		nfs4_stateid_copy(dst, &lsp->ls_stateid);
		ret = 0;
	}
	spin_unlock(&state->state_lock);
	nfs4_put_lock_state(lsp);
out:
	return ret;
}