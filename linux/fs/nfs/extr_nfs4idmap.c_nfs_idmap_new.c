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
struct rpc_pipe {int dummy; } ;
struct nfs_client {struct idmap* cl_idmap; TYPE_1__* cl_rpcclient; int /*<<< orphan*/  cl_net; } ;
struct idmap {int /*<<< orphan*/  cred; struct rpc_pipe* idmap_pipe; int /*<<< orphan*/  idmap_pdo; int /*<<< orphan*/  idmap_mutex; } ;
struct TYPE_2__ {int /*<<< orphan*/  cl_pipedir_objects; int /*<<< orphan*/  cl_cred; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct rpc_pipe*) ; 
 int PTR_ERR (struct rpc_pipe*) ; 
 int /*<<< orphan*/  get_cred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idmap_upcall_ops ; 
 int /*<<< orphan*/  kfree (struct idmap*) ; 
 struct idmap* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_idmap_pipe_dir_object_ops ; 
 int /*<<< orphan*/  put_cred (int /*<<< orphan*/ ) ; 
 int rpc_add_pipe_dir_object (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_destroy_pipe_data (struct rpc_pipe*) ; 
 int /*<<< orphan*/  rpc_init_pipe_dir_object (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct idmap*) ; 
 struct rpc_pipe* rpc_mkpipe_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
nfs_idmap_new(struct nfs_client *clp)
{
	struct idmap *idmap;
	struct rpc_pipe *pipe;
	int error;

	idmap = kzalloc(sizeof(*idmap), GFP_KERNEL);
	if (idmap == NULL)
		return -ENOMEM;

	mutex_init(&idmap->idmap_mutex);
	idmap->cred = get_cred(clp->cl_rpcclient->cl_cred);

	rpc_init_pipe_dir_object(&idmap->idmap_pdo,
			&nfs_idmap_pipe_dir_object_ops,
			idmap);

	pipe = rpc_mkpipe_data(&idmap_upcall_ops, 0);
	if (IS_ERR(pipe)) {
		error = PTR_ERR(pipe);
		goto err;
	}
	idmap->idmap_pipe = pipe;

	error = rpc_add_pipe_dir_object(clp->cl_net,
			&clp->cl_rpcclient->cl_pipedir_objects,
			&idmap->idmap_pdo);
	if (error)
		goto err_destroy_pipe;

	clp->cl_idmap = idmap;
	return 0;
err_destroy_pipe:
	rpc_destroy_pipe_data(idmap->idmap_pipe);
err:
	put_cred(idmap->cred);
	kfree(idmap);
	return error;
}