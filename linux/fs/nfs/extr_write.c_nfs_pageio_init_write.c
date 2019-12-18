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
struct nfs_server {int /*<<< orphan*/  wsize; TYPE_1__* pnfs_curr_ld; } ;
struct nfs_pgio_completion_ops {int dummy; } ;
struct nfs_pageio_ops {int dummy; } ;
struct nfs_pageio_descriptor {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {struct nfs_pageio_ops* pg_write_ops; } ;

/* Variables and functions */
 struct nfs_server* NFS_SERVER (struct inode*) ; 
 int /*<<< orphan*/  nfs_pageio_init (struct nfs_pageio_descriptor*,struct inode*,struct nfs_pageio_ops const*,struct nfs_pgio_completion_ops const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct nfs_pageio_ops nfs_pgio_rw_ops ; 
 int /*<<< orphan*/  nfs_rw_write_ops ; 

void nfs_pageio_init_write(struct nfs_pageio_descriptor *pgio,
			       struct inode *inode, int ioflags, bool force_mds,
			       const struct nfs_pgio_completion_ops *compl_ops)
{
	struct nfs_server *server = NFS_SERVER(inode);
	const struct nfs_pageio_ops *pg_ops = &nfs_pgio_rw_ops;

#ifdef CONFIG_NFS_V4_1
	if (server->pnfs_curr_ld && !force_mds)
		pg_ops = server->pnfs_curr_ld->pg_write_ops;
#endif
	nfs_pageio_init(pgio, inode, pg_ops, compl_ops, &nfs_rw_write_ops,
			server->wsize, ioflags);
}