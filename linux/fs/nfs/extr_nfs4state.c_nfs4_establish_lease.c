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
struct nfs_client {TYPE_1__* cl_mvops; } ;
struct nfs4_state_recovery_ops {int (* establish_clid ) (struct nfs_client*,struct cred const*) ;} ;
struct cred {int dummy; } ;
struct TYPE_2__ {struct nfs4_state_recovery_ops* reboot_recovery_ops; } ;

/* Variables and functions */
 int ENOENT ; 
 int nfs4_begin_drain_session (struct nfs_client*) ; 
 struct cred* nfs4_get_clid_cred (struct nfs_client*) ; 
 int /*<<< orphan*/  pnfs_destroy_all_layouts (struct nfs_client*) ; 
 int /*<<< orphan*/  put_cred (struct cred const*) ; 
 int stub1 (struct nfs_client*,struct cred const*) ; 

__attribute__((used)) static int nfs4_establish_lease(struct nfs_client *clp)
{
	const struct cred *cred;
	const struct nfs4_state_recovery_ops *ops =
		clp->cl_mvops->reboot_recovery_ops;
	int status;

	status = nfs4_begin_drain_session(clp);
	if (status != 0)
		return status;
	cred = nfs4_get_clid_cred(clp);
	if (cred == NULL)
		return -ENOENT;
	status = ops->establish_clid(clp, cred);
	put_cred(cred);
	if (status != 0)
		return status;
	pnfs_destroy_all_layouts(clp);
	return 0;
}