#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nfsd4_rename {int /*<<< orphan*/  rn_tinfo; int /*<<< orphan*/  rn_sinfo; int /*<<< orphan*/  rn_tnamelen; int /*<<< orphan*/  rn_tname; int /*<<< orphan*/  rn_snamelen; int /*<<< orphan*/  rn_sname; } ;
union nfsd4_op_u {struct nfsd4_rename rename; } ;
struct svc_rqst {int dummy; } ;
struct TYPE_6__ {TYPE_1__* fh_export; } ;
struct nfsd4_compound_state {TYPE_2__ save_fh; TYPE_2__ current_fh; } ;
typedef  scalar_t__ __be32 ;
struct TYPE_5__ {int ex_flags; } ;

/* Variables and functions */
 int NFSEXP_NOSUBTREECHECK ; 
 int /*<<< orphan*/  SVC_NET (struct svc_rqst*) ; 
 scalar_t__ nfs_ok ; 
 scalar_t__ nfsd_rename (struct svc_rqst*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nfserr_grace ; 
 scalar_t__ opens_in_grace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_change_info (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static __be32
nfsd4_rename(struct svc_rqst *rqstp, struct nfsd4_compound_state *cstate,
	     union nfsd4_op_u *u)
{
	struct nfsd4_rename *rename = &u->rename;
	__be32 status;

	if (opens_in_grace(SVC_NET(rqstp)) &&
		!(cstate->save_fh.fh_export->ex_flags & NFSEXP_NOSUBTREECHECK))
		return nfserr_grace;
	status = nfsd_rename(rqstp, &cstate->save_fh, rename->rn_sname,
			     rename->rn_snamelen, &cstate->current_fh,
			     rename->rn_tname, rename->rn_tnamelen);
	if (status)
		return status;
	set_change_info(&rename->rn_sinfo, &cstate->current_fh);
	set_change_info(&rename->rn_tinfo, &cstate->save_fh);
	return nfs_ok;
}