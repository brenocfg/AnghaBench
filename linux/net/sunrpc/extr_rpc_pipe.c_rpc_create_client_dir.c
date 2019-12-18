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
 int /*<<< orphan*/  IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  rpc_clntdir_populate ; 
 int /*<<< orphan*/  rpc_create_pipe_dir_objects (TYPE_1__*) ; 
 struct dentry* rpc_mkdir_populate (struct dentry*,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct rpc_clnt*) ; 

struct dentry *rpc_create_client_dir(struct dentry *dentry,
				   const char *name,
				   struct rpc_clnt *rpc_client)
{
	struct dentry *ret;

	ret = rpc_mkdir_populate(dentry, name, 0555, NULL,
				 rpc_clntdir_populate, rpc_client);
	if (!IS_ERR(ret)) {
		rpc_client->cl_pipedir_objects.pdh_dentry = ret;
		rpc_create_pipe_dir_objects(&rpc_client->cl_pipedir_objects);
	}
	return ret;
}