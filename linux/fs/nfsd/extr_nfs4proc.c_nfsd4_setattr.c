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
struct TYPE_3__ {int ia_valid; } ;
struct TYPE_4__ {scalar_t__ len; } ;
struct nfsd4_setattr {TYPE_1__ sa_iattr; TYPE_2__ sa_label; int /*<<< orphan*/ * sa_acl; int /*<<< orphan*/  sa_bmval; int /*<<< orphan*/  sa_stateid; } ;
union nfsd4_op_u {struct nfsd4_setattr setattr; } ;
typedef  int /*<<< orphan*/  time_t ;
struct svc_rqst {int dummy; } ;
struct nfsd4_compound_state {int /*<<< orphan*/  current_fh; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int ATTR_SIZE ; 
 int /*<<< orphan*/  WR_STATE ; 
 scalar_t__ check_attr_support (struct svc_rqst*,struct nfsd4_compound_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  fh_drop_write (int /*<<< orphan*/ *) ; 
 int fh_want_write (int /*<<< orphan*/ *) ; 
 scalar_t__ nfs4_preprocess_stateid_op (struct svc_rqst*,struct nfsd4_compound_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ nfs_ok ; 
 scalar_t__ nfsd4_set_nfs4_acl (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ nfsd4_set_nfs4_label (struct svc_rqst*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  nfsd_attrmask ; 
 scalar_t__ nfsd_setattr (struct svc_rqst*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nfserrno (int) ; 

__attribute__((used)) static __be32
nfsd4_setattr(struct svc_rqst *rqstp, struct nfsd4_compound_state *cstate,
	      union nfsd4_op_u *u)
{
	struct nfsd4_setattr *setattr = &u->setattr;
	__be32 status = nfs_ok;
	int err;

	if (setattr->sa_iattr.ia_valid & ATTR_SIZE) {
		status = nfs4_preprocess_stateid_op(rqstp, cstate,
				&cstate->current_fh, &setattr->sa_stateid,
				WR_STATE, NULL);
		if (status) {
			dprintk("NFSD: nfsd4_setattr: couldn't process stateid!\n");
			return status;
		}
	}
	err = fh_want_write(&cstate->current_fh);
	if (err)
		return nfserrno(err);
	status = nfs_ok;

	status = check_attr_support(rqstp, cstate, setattr->sa_bmval,
				    nfsd_attrmask);
	if (status)
		goto out;

	if (setattr->sa_acl != NULL)
		status = nfsd4_set_nfs4_acl(rqstp, &cstate->current_fh,
					    setattr->sa_acl);
	if (status)
		goto out;
	if (setattr->sa_label.len)
		status = nfsd4_set_nfs4_label(rqstp, &cstate->current_fh,
				&setattr->sa_label);
	if (status)
		goto out;
	status = nfsd_setattr(rqstp, &cstate->current_fh, &setattr->sa_iattr,
				0, (time_t)0);
out:
	fh_drop_write(&cstate->current_fh);
	return status;
}