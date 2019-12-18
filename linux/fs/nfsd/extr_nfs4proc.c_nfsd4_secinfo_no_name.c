#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int sin_style; int /*<<< orphan*/  sin_exp; } ;
union nfsd4_op_u {TYPE_1__ secinfo_no_name; } ;
struct svc_rqst {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  fh_export; } ;
struct nfsd4_compound_state {TYPE_2__ current_fh; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
#define  NFS4_SECINFO_STYLE4_CURRENT_FH 129 
#define  NFS4_SECINFO_STYLE4_PARENT 128 
 int /*<<< orphan*/  exp_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fh_put (TYPE_2__*) ; 
 int /*<<< orphan*/  nfs_ok ; 
 int /*<<< orphan*/  nfsd4_do_lookupp (struct svc_rqst*,TYPE_2__*) ; 
 int /*<<< orphan*/  nfserr_inval ; 

__attribute__((used)) static __be32
nfsd4_secinfo_no_name(struct svc_rqst *rqstp, struct nfsd4_compound_state *cstate,
		union nfsd4_op_u *u)
{
	__be32 err;

	switch (u->secinfo_no_name.sin_style) {
	case NFS4_SECINFO_STYLE4_CURRENT_FH:
		break;
	case NFS4_SECINFO_STYLE4_PARENT:
		err = nfsd4_do_lookupp(rqstp, &cstate->current_fh);
		if (err)
			return err;
		break;
	default:
		return nfserr_inval;
	}

	u->secinfo_no_name.sin_exp = exp_get(cstate->current_fh.fh_export);
	fh_put(&cstate->current_fh);
	return nfs_ok;
}