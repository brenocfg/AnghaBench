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
struct nfs_seqid {int dummy; } ;
struct nfs_open_context {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  stateid; struct nfs_seqid* seqid; int /*<<< orphan*/ * fl; int /*<<< orphan*/  fh; } ;
struct TYPE_3__ {struct nfs_seqid* seqid; } ;
struct nfs4_unlockdata {TYPE_2__ arg; int /*<<< orphan*/  server; int /*<<< orphan*/  fl; int /*<<< orphan*/  l_ctx; int /*<<< orphan*/  ctx; struct nfs4_lock_state* lsp; TYPE_1__ res; } ;
struct nfs4_state {int /*<<< orphan*/  state_lock; struct inode* inode; } ;
struct nfs4_lock_state {int /*<<< orphan*/  ls_stateid; struct nfs4_state* ls_state; } ;
struct inode {int dummy; } ;
struct file_lock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  NFS_FH (struct inode*) ; 
 int /*<<< orphan*/  NFS_SERVER (struct inode*) ; 
 int /*<<< orphan*/  get_nfs_open_context (struct nfs_open_context*) ; 
 struct nfs4_unlockdata* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  locks_copy_lock (int /*<<< orphan*/ *,struct file_lock*) ; 
 int /*<<< orphan*/  locks_init_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_stateid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_get_lock_context (struct nfs_open_context*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nfs4_unlockdata *nfs4_alloc_unlockdata(struct file_lock *fl,
		struct nfs_open_context *ctx,
		struct nfs4_lock_state *lsp,
		struct nfs_seqid *seqid)
{
	struct nfs4_unlockdata *p;
	struct nfs4_state *state = lsp->ls_state;
	struct inode *inode = state->inode;

	p = kzalloc(sizeof(*p), GFP_NOFS);
	if (p == NULL)
		return NULL;
	p->arg.fh = NFS_FH(inode);
	p->arg.fl = &p->fl;
	p->arg.seqid = seqid;
	p->res.seqid = seqid;
	p->lsp = lsp;
	/* Ensure we don't close file until we're done freeing locks! */
	p->ctx = get_nfs_open_context(ctx);
	p->l_ctx = nfs_get_lock_context(ctx);
	locks_init_lock(&p->fl);
	locks_copy_lock(&p->fl, fl);
	p->server = NFS_SERVER(inode);
	spin_lock(&state->state_lock);
	nfs4_stateid_copy(&p->arg.stateid, &lsp->ls_stateid);
	spin_unlock(&state->state_lock);
	return p;
}