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
struct rpc_task {int dummy; } ;
struct nfs_pgio_header {int (* pgio_done_cb ) (struct rpc_task*,struct nfs_pgio_header*) ;int /*<<< orphan*/  fattr; struct inode* inode; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ nfs3_async_handle_jukebox (struct rpc_task*,struct inode*) ; 
 int /*<<< orphan*/  nfs_invalidate_atime (struct inode*) ; 
 int /*<<< orphan*/  nfs_refresh_inode (struct inode*,int /*<<< orphan*/ *) ; 
 int stub1 (struct rpc_task*,struct nfs_pgio_header*) ; 

__attribute__((used)) static int nfs3_read_done(struct rpc_task *task, struct nfs_pgio_header *hdr)
{
	struct inode *inode = hdr->inode;

	if (hdr->pgio_done_cb != NULL)
		return hdr->pgio_done_cb(task, hdr);

	if (nfs3_async_handle_jukebox(task, inode))
		return -EAGAIN;

	nfs_invalidate_atime(inode);
	nfs_refresh_inode(inode, &hdr->fattr);
	return 0;
}