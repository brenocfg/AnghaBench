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
struct nfsd4_rename {int /*<<< orphan*/  rn_tinfo; int /*<<< orphan*/  rn_sinfo; int /*<<< orphan*/  rn_tnamelen; int /*<<< orphan*/  rn_tname; int /*<<< orphan*/  rn_snamelen; int /*<<< orphan*/  rn_sname; } ;
union nfsd4_op_u {struct nfsd4_rename rename; } ;
struct svc_rqst {int dummy; } ;
struct nfsd4_compound_state {int /*<<< orphan*/  save_fh; int /*<<< orphan*/  current_fh; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  SVC_NET (struct svc_rqst*) ; 
 scalar_t__ nfs_ok ; 
 scalar_t__ nfsd_rename (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nfserr_grace ; 
 scalar_t__ opens_in_grace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_change_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __be32
nfsd4_rename(struct svc_rqst *rqstp, struct nfsd4_compound_state *cstate,
	     union nfsd4_op_u *u)
{
	struct nfsd4_rename *rename = &u->rename;
	__be32 status;

	if (opens_in_grace(SVC_NET(rqstp)))
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