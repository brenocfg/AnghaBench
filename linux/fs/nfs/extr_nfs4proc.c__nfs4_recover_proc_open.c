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
struct nfs_openres {int rflags; } ;
struct nfs4_opendata {int /*<<< orphan*/  f_attr; int /*<<< orphan*/  rpc_done; struct nfs_openres o_res; int /*<<< orphan*/  dir; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int NFS4_OPEN_RESULT_CONFIRM ; 
 int /*<<< orphan*/  NFS_SERVER (struct inode*) ; 
 int _nfs4_proc_open_confirm (struct nfs4_opendata*) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int nfs4_run_open_task (struct nfs4_opendata*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_fattr_map_and_free_names (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int _nfs4_recover_proc_open(struct nfs4_opendata *data)
{
	struct inode *dir = d_inode(data->dir);
	struct nfs_openres *o_res = &data->o_res;
	int status;

	status = nfs4_run_open_task(data, NULL);
	if (status != 0 || !data->rpc_done)
		return status;

	nfs_fattr_map_and_free_names(NFS_SERVER(dir), &data->f_attr);

	if (o_res->rflags & NFS4_OPEN_RESULT_CONFIRM)
		status = _nfs4_proc_open_confirm(data);

	return status;
}