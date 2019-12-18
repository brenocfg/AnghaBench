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
struct nfs_client {TYPE_1__* cl_rpcclient; int /*<<< orphan*/  cl_net; struct idmap* cl_idmap; } ;
struct idmap {int /*<<< orphan*/  cred; int /*<<< orphan*/  idmap_pipe; int /*<<< orphan*/  idmap_pdo; } ;
struct TYPE_2__ {int /*<<< orphan*/  cl_pipedir_objects; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct idmap*) ; 
 int /*<<< orphan*/  put_cred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_destroy_pipe_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_remove_pipe_dir_object (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
nfs_idmap_delete(struct nfs_client *clp)
{
	struct idmap *idmap = clp->cl_idmap;

	if (!idmap)
		return;
	clp->cl_idmap = NULL;
	rpc_remove_pipe_dir_object(clp->cl_net,
			&clp->cl_rpcclient->cl_pipedir_objects,
			&idmap->idmap_pdo);
	rpc_destroy_pipe_data(idmap->idmap_pipe);
	put_cred(idmap->cred);
	kfree(idmap);
}