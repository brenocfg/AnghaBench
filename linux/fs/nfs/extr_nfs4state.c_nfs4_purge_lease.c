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
struct nfs_client {int /*<<< orphan*/  cl_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4CLNT_LEASE_EXPIRED ; 
 int /*<<< orphan*/  NFS4CLNT_PURGE_STATE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int nfs4_establish_lease (struct nfs_client*) ; 
 int nfs4_handle_reclaim_lease_error (struct nfs_client*,int) ; 
 int /*<<< orphan*/  nfs4_state_start_reclaim_nograce (struct nfs_client*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfs4_purge_lease(struct nfs_client *clp)
{
	int status;

	status = nfs4_establish_lease(clp);
	if (status < 0)
		return nfs4_handle_reclaim_lease_error(clp, status);
	clear_bit(NFS4CLNT_PURGE_STATE, &clp->cl_state);
	set_bit(NFS4CLNT_LEASE_EXPIRED, &clp->cl_state);
	nfs4_state_start_reclaim_nograce(clp);
	return 0;
}