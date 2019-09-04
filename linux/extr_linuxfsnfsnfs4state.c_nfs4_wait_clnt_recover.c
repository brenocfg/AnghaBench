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
struct nfs_client {int cl_cons_state; int /*<<< orphan*/  cl_state; int /*<<< orphan*/  cl_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4CLNT_MANAGER_RUNNING ; 
 int /*<<< orphan*/  TASK_KILLABLE ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  nfs_put_client (struct nfs_client*) ; 
 int /*<<< orphan*/  nfs_wait_bit_killable ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int wait_on_bit_action (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int nfs4_wait_clnt_recover(struct nfs_client *clp)
{
	int res;

	might_sleep();

	refcount_inc(&clp->cl_count);
	res = wait_on_bit_action(&clp->cl_state, NFS4CLNT_MANAGER_RUNNING,
				 nfs_wait_bit_killable, TASK_KILLABLE);
	if (res)
		goto out;
	if (clp->cl_cons_state < 0)
		res = clp->cl_cons_state;
out:
	nfs_put_client(clp);
	return res;
}