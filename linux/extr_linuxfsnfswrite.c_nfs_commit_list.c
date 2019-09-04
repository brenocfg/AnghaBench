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
struct nfs_commit_info {TYPE_1__* mds; } ;
struct nfs_commit_data {int /*<<< orphan*/  mds_ops; } ;
struct list_head {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rpcs_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_CLIENT (struct inode*) ; 
 int /*<<< orphan*/  NFS_PROTO (struct inode*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (struct list_head*) ; 
 struct nfs_commit_data* nfs_commitdata_alloc (int) ; 
 int /*<<< orphan*/  nfs_init_commit (struct nfs_commit_data*,struct list_head*,int /*<<< orphan*/ *,struct nfs_commit_info*) ; 
 int nfs_initiate_commit (int /*<<< orphan*/ ,struct nfs_commit_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs_commit_list(struct inode *inode, struct list_head *head, int how,
		struct nfs_commit_info *cinfo)
{
	struct nfs_commit_data	*data;

	/* another commit raced with us */
	if (list_empty(head))
		return 0;

	data = nfs_commitdata_alloc(true);

	/* Set up the argument struct */
	nfs_init_commit(data, head, NULL, cinfo);
	atomic_inc(&cinfo->mds->rpcs_out);
	return nfs_initiate_commit(NFS_CLIENT(inode), data, NFS_PROTO(inode),
				   data->mds_ops, how, 0);
}