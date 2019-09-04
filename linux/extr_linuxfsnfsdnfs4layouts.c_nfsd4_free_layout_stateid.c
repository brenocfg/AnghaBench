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
struct nfs4_stid {int dummy; } ;
struct TYPE_3__ {struct nfs4_file* sc_file; int /*<<< orphan*/  sc_stateid; struct nfs4_client* sc_client; } ;
struct nfs4_layout_stateid {size_t ls_layout_type; TYPE_1__ ls_stid; scalar_t__ ls_recalled; int /*<<< orphan*/  ls_file; int /*<<< orphan*/  ls_perfile; int /*<<< orphan*/  ls_perclnt; } ;
struct nfs4_file {int /*<<< orphan*/  fi_lo_recalls; int /*<<< orphan*/  fi_lock; } ;
struct nfs4_client {int /*<<< orphan*/  cl_lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  disable_recalls; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_UNLCK ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct nfs4_layout_stateid*) ; 
 struct nfs4_layout_stateid* layoutstateid (struct nfs4_stid*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_layout_stateid_cache ; 
 TYPE_2__** nfsd4_layout_ops ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_nfsd_layoutstate_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfs_setlease (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 

__attribute__((used)) static void
nfsd4_free_layout_stateid(struct nfs4_stid *stid)
{
	struct nfs4_layout_stateid *ls = layoutstateid(stid);
	struct nfs4_client *clp = ls->ls_stid.sc_client;
	struct nfs4_file *fp = ls->ls_stid.sc_file;

	trace_nfsd_layoutstate_free(&ls->ls_stid.sc_stateid);

	spin_lock(&clp->cl_lock);
	list_del_init(&ls->ls_perclnt);
	spin_unlock(&clp->cl_lock);

	spin_lock(&fp->fi_lock);
	list_del_init(&ls->ls_perfile);
	spin_unlock(&fp->fi_lock);

	if (!nfsd4_layout_ops[ls->ls_layout_type]->disable_recalls)
		vfs_setlease(ls->ls_file, F_UNLCK, NULL, (void **)&ls);
	fput(ls->ls_file);

	if (ls->ls_recalled)
		atomic_dec(&ls->ls_stid.sc_file->fi_lo_recalls);

	kmem_cache_free(nfs4_layout_stateid_cache, ls);
}