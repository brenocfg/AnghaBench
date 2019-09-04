#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rpc_task {int dummy; } ;
struct nfs_commit_data {int /*<<< orphan*/  inode; } ;
struct TYPE_4__ {TYPE_1__* client; } ;
struct TYPE_3__ {int /*<<< orphan*/  cl_metrics; } ;

/* Variables and functions */
 TYPE_2__* NFS_SERVER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_count_iostats (struct rpc_task*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void filelayout_commit_count_stats(struct rpc_task *task, void *data)
{
	struct nfs_commit_data *cdata = data;

	rpc_count_iostats(task, NFS_SERVER(cdata->inode)->client->cl_metrics);
}