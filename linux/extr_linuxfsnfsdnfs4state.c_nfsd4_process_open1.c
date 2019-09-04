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
struct nfsd_net {int dummy; } ;
struct nfsd4_open {int /*<<< orphan*/  op_odstate; int /*<<< orphan*/  op_stp; struct nfs4_openowner* op_openowner; int /*<<< orphan*/  op_seqid; int /*<<< orphan*/  op_owner; int /*<<< orphan*/ * op_file; int /*<<< orphan*/  op_clientid; } ;
struct TYPE_4__ {TYPE_1__* fh_export; } ;
struct nfsd4_compound_state {TYPE_2__ current_fh; struct nfs4_client* clp; } ;
struct nfs4_openowner {int oo_flags; int /*<<< orphan*/  oo_owner; } ;
struct nfs4_client {int dummy; } ;
typedef  int /*<<< orphan*/  clientid_t ;
typedef  scalar_t__ __be32 ;
struct TYPE_3__ {int ex_flags; } ;

/* Variables and functions */
 int NFS4_OO_CONFIRMED ; 
 int NFSEXP_PNFS ; 
 scalar_t__ STALE_CLIENTID (int /*<<< orphan*/ *,struct nfsd_net*) ; 
 int /*<<< orphan*/  alloc_clnt_odstate (struct nfs4_client*) ; 
 struct nfs4_openowner* alloc_init_open_stateowner (unsigned int,struct nfsd4_open*,struct nfsd4_compound_state*) ; 
 struct nfs4_openowner* find_openstateowner_str (unsigned int,struct nfsd4_open*,struct nfs4_client*) ; 
 scalar_t__ lookup_clientid (int /*<<< orphan*/ *,struct nfsd4_compound_state*,struct nfsd_net*) ; 
 int /*<<< orphan*/  nfs4_alloc_open_stateid (struct nfs4_client*) ; 
 scalar_t__ nfs_ok ; 
 int /*<<< orphan*/ * nfsd4_alloc_file () ; 
 scalar_t__ nfsd4_check_seqid (struct nfsd4_compound_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ nfsd4_has_session (struct nfsd4_compound_state*) ; 
 scalar_t__ nfserr_jukebox ; 
 scalar_t__ nfserr_stale_clientid ; 
 unsigned int ownerstr_hashval (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_openowner (struct nfs4_openowner*) ; 

__be32
nfsd4_process_open1(struct nfsd4_compound_state *cstate,
		    struct nfsd4_open *open, struct nfsd_net *nn)
{
	clientid_t *clientid = &open->op_clientid;
	struct nfs4_client *clp = NULL;
	unsigned int strhashval;
	struct nfs4_openowner *oo = NULL;
	__be32 status;

	if (STALE_CLIENTID(&open->op_clientid, nn))
		return nfserr_stale_clientid;
	/*
	 * In case we need it later, after we've already created the
	 * file and don't want to risk a further failure:
	 */
	open->op_file = nfsd4_alloc_file();
	if (open->op_file == NULL)
		return nfserr_jukebox;

	status = lookup_clientid(clientid, cstate, nn);
	if (status)
		return status;
	clp = cstate->clp;

	strhashval = ownerstr_hashval(&open->op_owner);
	oo = find_openstateowner_str(strhashval, open, clp);
	open->op_openowner = oo;
	if (!oo) {
		goto new_owner;
	}
	if (!(oo->oo_flags & NFS4_OO_CONFIRMED)) {
		/* Replace unconfirmed owners without checking for replay. */
		release_openowner(oo);
		open->op_openowner = NULL;
		goto new_owner;
	}
	status = nfsd4_check_seqid(cstate, &oo->oo_owner, open->op_seqid);
	if (status)
		return status;
	goto alloc_stateid;
new_owner:
	oo = alloc_init_open_stateowner(strhashval, open, cstate);
	if (oo == NULL)
		return nfserr_jukebox;
	open->op_openowner = oo;
alloc_stateid:
	open->op_stp = nfs4_alloc_open_stateid(clp);
	if (!open->op_stp)
		return nfserr_jukebox;

	if (nfsd4_has_session(cstate) &&
	    (cstate->current_fh.fh_export->ex_flags & NFSEXP_PNFS)) {
		open->op_odstate = alloc_clnt_odstate(clp);
		if (!open->op_odstate)
			return nfserr_jukebox;
	}

	return nfs_ok;
}