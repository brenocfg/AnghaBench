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
struct TYPE_2__ {struct dentry* pdh_dentry; } ;
struct rpc_clnt {TYPE_1__ cl_pipedir_objects; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rpc_clntdir_depopulate ; 
 int /*<<< orphan*/  rpc_destroy_pipe_dir_objects (TYPE_1__*) ; 
 int rpc_rmdir_depopulate (struct dentry*,int /*<<< orphan*/ ) ; 

int rpc_remove_client_dir(struct rpc_clnt *rpc_client)
{
	struct dentry *dentry = rpc_client->cl_pipedir_objects.pdh_dentry;

	if (dentry == NULL)
		return 0;
	rpc_destroy_pipe_dir_objects(&rpc_client->cl_pipedir_objects);
	rpc_client->cl_pipedir_objects.pdh_dentry = NULL;
	return rpc_rmdir_depopulate(dentry, rpc_clntdir_depopulate);
}