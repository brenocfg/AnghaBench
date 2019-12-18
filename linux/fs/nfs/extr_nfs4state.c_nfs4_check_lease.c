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
struct nfs_client {int /*<<< orphan*/  cl_state; TYPE_1__* cl_mvops; } ;
struct nfs4_state_maintenance_ops {int (* renew_lease ) (struct nfs_client*,struct cred const*) ;struct cred* (* get_state_renewal_cred ) (struct nfs_client*) ;} ;
struct cred {int dummy; } ;
struct TYPE_2__ {struct nfs4_state_maintenance_ops* state_renewal_ops; } ;

/* Variables and functions */
 int ENOKEY ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  NFS4CLNT_CHECK_LEASE ; 
 int /*<<< orphan*/  NFS4CLNT_LEASE_EXPIRED ; 
 struct cred* nfs4_get_clid_cred (struct nfs_client*) ; 
 int nfs4_recovery_handle_error (struct nfs_client*,int) ; 
 int /*<<< orphan*/  put_cred (struct cred const*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct cred* stub1 (struct nfs_client*) ; 
 int stub2 (struct nfs_client*,struct cred const*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfs4_check_lease(struct nfs_client *clp)
{
	const struct cred *cred;
	const struct nfs4_state_maintenance_ops *ops =
		clp->cl_mvops->state_renewal_ops;
	int status;

	/* Is the client already known to have an expired lease? */
	if (test_bit(NFS4CLNT_LEASE_EXPIRED, &clp->cl_state))
		return 0;
	cred = ops->get_state_renewal_cred(clp);
	if (cred == NULL) {
		cred = nfs4_get_clid_cred(clp);
		status = -ENOKEY;
		if (cred == NULL)
			goto out;
	}
	status = ops->renew_lease(clp, cred);
	put_cred(cred);
	if (status == -ETIMEDOUT) {
		set_bit(NFS4CLNT_CHECK_LEASE, &clp->cl_state);
		return 0;
	}
out:
	return nfs4_recovery_handle_error(clp, status);
}