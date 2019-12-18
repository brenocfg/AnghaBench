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
typedef  int /*<<< orphan*/  u32 ;
struct nfsd4_compound_state {struct nfs4_client* clp; } ;
struct nfs4_stid {scalar_t__ sc_type; struct nfs4_file* sc_file; } ;
struct TYPE_2__ {int /*<<< orphan*/  sc_stateid; } ;
struct nfs4_layout_stateid {TYPE_1__ ls_stid; int /*<<< orphan*/  ls_perfile; int /*<<< orphan*/  ls_perclnt; int /*<<< orphan*/  ls_file; int /*<<< orphan*/  ls_recall; int /*<<< orphan*/  ls_layout_type; int /*<<< orphan*/  ls_mutex; int /*<<< orphan*/  ls_layouts; int /*<<< orphan*/  ls_lock; } ;
struct nfs4_file {int /*<<< orphan*/  fi_lock; int /*<<< orphan*/  fi_lo_states; int /*<<< orphan*/  fi_deleg_file; } ;
struct nfs4_client {int /*<<< orphan*/  cl_lock; int /*<<< orphan*/  cl_lo_states; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ NFS4_DELEG_STID ; 
 scalar_t__ NFS4_LAYOUT_STID ; 
 int /*<<< orphan*/  NFSPROC4_CLNT_CB_LAYOUT ; 
 int /*<<< orphan*/  find_any_file (struct nfs4_file*) ; 
 int /*<<< orphan*/  get_nfs4_file (struct nfs4_file*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct nfs4_layout_stateid*) ; 
 struct nfs4_layout_stateid* layoutstateid (struct nfs4_stid*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct nfs4_stid* nfs4_alloc_stid (struct nfs4_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_layout_stateid_cache ; 
 int /*<<< orphan*/  nfsd4_cb_layout_ops ; 
 int /*<<< orphan*/  nfsd4_free_layout_stateid ; 
 int /*<<< orphan*/  nfsd4_init_cb (int /*<<< orphan*/ *,struct nfs4_client*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ nfsd4_layout_setlease (struct nfs4_layout_stateid*) ; 
 int /*<<< orphan*/  nfsd_file_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_file_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_nfs4_file (struct nfs4_file*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_nfsd_layoutstate_alloc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nfs4_layout_stateid *
nfsd4_alloc_layout_stateid(struct nfsd4_compound_state *cstate,
		struct nfs4_stid *parent, u32 layout_type)
{
	struct nfs4_client *clp = cstate->clp;
	struct nfs4_file *fp = parent->sc_file;
	struct nfs4_layout_stateid *ls;
	struct nfs4_stid *stp;

	stp = nfs4_alloc_stid(cstate->clp, nfs4_layout_stateid_cache,
					nfsd4_free_layout_stateid);
	if (!stp)
		return NULL;

	get_nfs4_file(fp);
	stp->sc_file = fp;

	ls = layoutstateid(stp);
	INIT_LIST_HEAD(&ls->ls_perclnt);
	INIT_LIST_HEAD(&ls->ls_perfile);
	spin_lock_init(&ls->ls_lock);
	INIT_LIST_HEAD(&ls->ls_layouts);
	mutex_init(&ls->ls_mutex);
	ls->ls_layout_type = layout_type;
	nfsd4_init_cb(&ls->ls_recall, clp, &nfsd4_cb_layout_ops,
			NFSPROC4_CLNT_CB_LAYOUT);

	if (parent->sc_type == NFS4_DELEG_STID)
		ls->ls_file = nfsd_file_get(fp->fi_deleg_file);
	else
		ls->ls_file = find_any_file(fp);
	BUG_ON(!ls->ls_file);

	if (nfsd4_layout_setlease(ls)) {
		nfsd_file_put(ls->ls_file);
		put_nfs4_file(fp);
		kmem_cache_free(nfs4_layout_stateid_cache, ls);
		return NULL;
	}

	spin_lock(&clp->cl_lock);
	stp->sc_type = NFS4_LAYOUT_STID;
	list_add(&ls->ls_perclnt, &clp->cl_lo_states);
	spin_unlock(&clp->cl_lock);

	spin_lock(&fp->fi_lock);
	list_add(&ls->ls_perfile, &fp->fi_lo_states);
	spin_unlock(&fp->fi_lock);

	trace_nfsd_layoutstate_alloc(&ls->ls_stid.sc_stateid);
	return ls;
}