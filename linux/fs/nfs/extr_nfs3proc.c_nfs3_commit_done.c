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
struct rpc_task {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fattr; } ;
struct nfs_commit_data {int (* commit_done_cb ) (struct rpc_task*,struct nfs_commit_data*) ;TYPE_1__ res; int /*<<< orphan*/  inode; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ nfs3_async_handle_jukebox (struct rpc_task*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_refresh_inode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct rpc_task*,struct nfs_commit_data*) ; 

__attribute__((used)) static int nfs3_commit_done(struct rpc_task *task, struct nfs_commit_data *data)
{
	if (data->commit_done_cb != NULL)
		return data->commit_done_cb(task, data);

	if (nfs3_async_handle_jukebox(task, data->inode))
		return -EAGAIN;
	nfs_refresh_inode(data->inode, data->res.fattr);
	return 0;
}