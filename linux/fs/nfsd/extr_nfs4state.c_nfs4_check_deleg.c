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
struct nfsd4_open {TYPE_1__* op_openowner; int /*<<< orphan*/  op_share_access; int /*<<< orphan*/  op_delegate_stateid; } ;
struct TYPE_4__ {scalar_t__ sc_type; } ;
struct nfs4_delegation {TYPE_2__ dl_stid; } ;
struct nfs4_client {scalar_t__ cl_minorversion; } ;
typedef  scalar_t__ __be32 ;
struct TYPE_3__ {int /*<<< orphan*/  oo_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4_OO_CONFIRMED ; 
 scalar_t__ NFS4_REVOKED_DELEG_STID ; 
 struct nfs4_delegation* find_deleg_stateid (struct nfs4_client*,int /*<<< orphan*/ *) ; 
 scalar_t__ nfs4_check_delegmode (struct nfs4_delegation*,int) ; 
 int /*<<< orphan*/  nfs4_put_stid (TYPE_2__*) ; 
 scalar_t__ nfs_ok ; 
 int /*<<< orphan*/  nfsd4_is_deleg_cur (struct nfsd4_open*) ; 
 scalar_t__ nfserr_bad_stateid ; 
 scalar_t__ nfserr_deleg_revoked ; 
 int share_access_to_flags (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32
nfs4_check_deleg(struct nfs4_client *cl, struct nfsd4_open *open,
		struct nfs4_delegation **dp)
{
	int flags;
	__be32 status = nfserr_bad_stateid;
	struct nfs4_delegation *deleg;

	deleg = find_deleg_stateid(cl, &open->op_delegate_stateid);
	if (deleg == NULL)
		goto out;
	if (deleg->dl_stid.sc_type == NFS4_REVOKED_DELEG_STID) {
		nfs4_put_stid(&deleg->dl_stid);
		if (cl->cl_minorversion)
			status = nfserr_deleg_revoked;
		goto out;
	}
	flags = share_access_to_flags(open->op_share_access);
	status = nfs4_check_delegmode(deleg, flags);
	if (status) {
		nfs4_put_stid(&deleg->dl_stid);
		goto out;
	}
	*dp = deleg;
out:
	if (!nfsd4_is_deleg_cur(open))
		return nfs_ok;
	if (status)
		return status;
	open->op_openowner->oo_flags |= NFS4_OO_CONFIRMED;
	return nfs_ok;
}