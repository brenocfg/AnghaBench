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
struct nfs_client {int /*<<< orphan*/  cl_owner_id; int /*<<< orphan*/  cl_implid; int /*<<< orphan*/  cl_serverscope; int /*<<< orphan*/  cl_serverowner; int /*<<< orphan*/  cl_rpcwaitq; int /*<<< orphan*/  cl_res_state; TYPE_1__* cl_mvops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* shutdown_client ) (struct nfs_client*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_CS_IDMAP ; 
 int /*<<< orphan*/  NFS_CS_RENEWD ; 
 scalar_t__ __test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_destroy_callback (struct nfs_client*) ; 
 int /*<<< orphan*/  nfs4_kill_renewd (struct nfs_client*) ; 
 int /*<<< orphan*/  nfs_idmap_delete (struct nfs_client*) ; 
 int /*<<< orphan*/  rpc_destroy_wait_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct nfs_client*) ; 

__attribute__((used)) static void nfs4_shutdown_client(struct nfs_client *clp)
{
	if (__test_and_clear_bit(NFS_CS_RENEWD, &clp->cl_res_state))
		nfs4_kill_renewd(clp);
	clp->cl_mvops->shutdown_client(clp);
	nfs4_destroy_callback(clp);
	if (__test_and_clear_bit(NFS_CS_IDMAP, &clp->cl_res_state))
		nfs_idmap_delete(clp);

	rpc_destroy_wait_queue(&clp->cl_rpcwaitq);
	kfree(clp->cl_serverowner);
	kfree(clp->cl_serverscope);
	kfree(clp->cl_implid);
	kfree(clp->cl_owner_id);
}