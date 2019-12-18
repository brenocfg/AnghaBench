#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nfs_server {struct nfs_client* nfs_client; } ;
struct nfs_client {TYPE_2__* cl_mvops; } ;
struct nfs4_state {TYPE_1__* owner; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  flags; int /*<<< orphan*/  lock_states; } ;
struct nfs4_lock_state {int /*<<< orphan*/  ls_flags; int /*<<< orphan*/  ls_locks; int /*<<< orphan*/  ls_count; struct nfs4_state* ls_state; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* free_lock_state ) (struct nfs_server*,struct nfs4_lock_state*) ;} ;
struct TYPE_3__ {struct nfs_server* so_server; } ;

/* Variables and functions */
 int /*<<< orphan*/  LK_STATE_IN_USE ; 
 int /*<<< orphan*/  NFS_LOCK_INITIALIZED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_free_lock_state (struct nfs_server*,struct nfs4_lock_state*) ; 
 int /*<<< orphan*/  refcount_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct nfs_server*,struct nfs4_lock_state*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void nfs4_put_lock_state(struct nfs4_lock_state *lsp)
{
	struct nfs_server *server;
	struct nfs4_state *state;

	if (lsp == NULL)
		return;
	state = lsp->ls_state;
	if (!refcount_dec_and_lock(&lsp->ls_count, &state->state_lock))
		return;
	list_del(&lsp->ls_locks);
	if (list_empty(&state->lock_states))
		clear_bit(LK_STATE_IN_USE, &state->flags);
	spin_unlock(&state->state_lock);
	server = state->owner->so_server;
	if (test_bit(NFS_LOCK_INITIALIZED, &lsp->ls_flags)) {
		struct nfs_client *clp = server->nfs_client;

		clp->cl_mvops->free_lock_state(server, lsp);
	} else
		nfs4_free_lock_state(server, lsp);
}