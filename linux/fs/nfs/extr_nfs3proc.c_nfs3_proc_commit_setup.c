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
struct rpc_message {int /*<<< orphan*/ * rpc_proc; } ;
struct rpc_clnt {int dummy; } ;
struct nfs_commit_data {int dummy; } ;

/* Variables and functions */
 size_t NFS3PROC_COMMIT ; 
 int /*<<< orphan*/ * nfs3_procedures ; 

__attribute__((used)) static void nfs3_proc_commit_setup(struct nfs_commit_data *data, struct rpc_message *msg,
				   struct rpc_clnt **clnt)
{
	msg->rpc_proc = &nfs3_procedures[NFS3PROC_COMMIT];
}