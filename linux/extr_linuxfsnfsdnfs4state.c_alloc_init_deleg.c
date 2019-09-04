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
struct svc_fh {int /*<<< orphan*/  fh_handle; } ;
struct nfs4_file {int dummy; } ;
struct TYPE_3__ {int si_generation; } ;
struct TYPE_4__ {struct nfs4_file* sc_file; int /*<<< orphan*/  sc_client; TYPE_1__ sc_stateid; } ;
struct nfs4_delegation {int dl_retries; TYPE_2__ dl_stid; int /*<<< orphan*/  dl_recall; int /*<<< orphan*/  dl_type; struct nfs4_clnt_odstate* dl_clnt_odstate; int /*<<< orphan*/  dl_recall_lru; int /*<<< orphan*/  dl_perclnt; int /*<<< orphan*/  dl_perfile; } ;
struct nfs4_clnt_odstate {int dummy; } ;
struct nfs4_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NFS4_OPEN_DELEGATE_READ ; 
 int /*<<< orphan*/  NFSPROC4_CLNT_CB_RECALL ; 
 int /*<<< orphan*/  atomic_long_dec (int /*<<< orphan*/ *) ; 
 long atomic_long_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deleg_slab ; 
 scalar_t__ delegation_blocked (int /*<<< orphan*/ *) ; 
 struct nfs4_delegation* delegstateid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  get_clnt_odstate (struct nfs4_clnt_odstate*) ; 
 int /*<<< orphan*/  get_nfs4_file (struct nfs4_file*) ; 
 long max_delegations ; 
 int /*<<< orphan*/  nfs4_alloc_stid (struct nfs4_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_free_deleg ; 
 int /*<<< orphan*/  nfsd4_cb_recall_ops ; 
 int /*<<< orphan*/  nfsd4_init_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  num_delegations ; 

__attribute__((used)) static struct nfs4_delegation *
alloc_init_deleg(struct nfs4_client *clp, struct nfs4_file *fp,
		 struct svc_fh *current_fh,
		 struct nfs4_clnt_odstate *odstate)
{
	struct nfs4_delegation *dp;
	long n;

	dprintk("NFSD alloc_init_deleg\n");
	n = atomic_long_inc_return(&num_delegations);
	if (n < 0 || n > max_delegations)
		goto out_dec;
	if (delegation_blocked(&current_fh->fh_handle))
		goto out_dec;
	dp = delegstateid(nfs4_alloc_stid(clp, deleg_slab, nfs4_free_deleg));
	if (dp == NULL)
		goto out_dec;

	/*
	 * delegation seqid's are never incremented.  The 4.1 special
	 * meaning of seqid 0 isn't meaningful, really, but let's avoid
	 * 0 anyway just for consistency and use 1:
	 */
	dp->dl_stid.sc_stateid.si_generation = 1;
	INIT_LIST_HEAD(&dp->dl_perfile);
	INIT_LIST_HEAD(&dp->dl_perclnt);
	INIT_LIST_HEAD(&dp->dl_recall_lru);
	dp->dl_clnt_odstate = odstate;
	get_clnt_odstate(odstate);
	dp->dl_type = NFS4_OPEN_DELEGATE_READ;
	dp->dl_retries = 1;
	nfsd4_init_cb(&dp->dl_recall, dp->dl_stid.sc_client,
		      &nfsd4_cb_recall_ops, NFSPROC4_CLNT_CB_RECALL);
	get_nfs4_file(fp);
	dp->dl_stid.sc_file = fp;
	return dp;
out_dec:
	atomic_long_dec(&num_delegations);
	return NULL;
}