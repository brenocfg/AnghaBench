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
struct nfs_fsinfo {int lease_time; } ;
struct nfs_client {int /*<<< orphan*/  cl_res_state; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  NFS_CS_CHECK_LEASE_TIME ; 
 unsigned long jiffies ; 
 int nfs4_proc_get_lease_time (struct nfs_client*,struct nfs_fsinfo*) ; 
 int /*<<< orphan*/  nfs4_schedule_state_renewal (struct nfs_client*) ; 
 int /*<<< orphan*/  nfs4_set_lease_period (struct nfs_client*,int,unsigned long) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfs4_setup_state_renewal(struct nfs_client *clp)
{
	int status;
	struct nfs_fsinfo fsinfo;
	unsigned long now;

	if (!test_bit(NFS_CS_CHECK_LEASE_TIME, &clp->cl_res_state)) {
		nfs4_schedule_state_renewal(clp);
		return 0;
	}

	now = jiffies;
	status = nfs4_proc_get_lease_time(clp, &fsinfo);
	if (status == 0) {
		nfs4_set_lease_period(clp, fsinfo.lease_time * HZ, now);
		nfs4_schedule_state_renewal(clp);
	}

	return status;
}