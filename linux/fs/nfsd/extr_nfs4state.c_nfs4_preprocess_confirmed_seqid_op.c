#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct nfsd_net {int dummy; } ;
struct nfsd4_compound_state {int dummy; } ;
struct nfs4_openowner {int oo_flags; } ;
struct nfs4_ol_stateid {int /*<<< orphan*/  st_stid; int /*<<< orphan*/  st_mutex; int /*<<< orphan*/  st_stateowner; } ;
typedef  int /*<<< orphan*/  stateid_t ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int NFS4_OO_CONFIRMED ; 
 int /*<<< orphan*/  NFS4_OPEN_STID ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ nfs4_preprocess_seqid_op (struct nfsd4_compound_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nfs4_ol_stateid**,struct nfsd_net*) ; 
 int /*<<< orphan*/  nfs4_put_stid (int /*<<< orphan*/ *) ; 
 scalar_t__ nfs_ok ; 
 scalar_t__ nfserr_bad_stateid ; 
 struct nfs4_openowner* openowner (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32 nfs4_preprocess_confirmed_seqid_op(struct nfsd4_compound_state *cstate, u32 seqid,
						 stateid_t *stateid, struct nfs4_ol_stateid **stpp, struct nfsd_net *nn)
{
	__be32 status;
	struct nfs4_openowner *oo;
	struct nfs4_ol_stateid *stp;

	status = nfs4_preprocess_seqid_op(cstate, seqid, stateid,
						NFS4_OPEN_STID, &stp, nn);
	if (status)
		return status;
	oo = openowner(stp->st_stateowner);
	if (!(oo->oo_flags & NFS4_OO_CONFIRMED)) {
		mutex_unlock(&stp->st_mutex);
		nfs4_put_stid(&stp->st_stid);
		return nfserr_bad_stateid;
	}
	*stpp = stp;
	return nfs_ok;
}