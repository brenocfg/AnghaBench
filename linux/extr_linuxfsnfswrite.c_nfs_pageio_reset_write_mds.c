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
struct nfs_pgio_mirror {int /*<<< orphan*/  pg_bsize; } ;
struct nfs_pageio_descriptor {int /*<<< orphan*/  pg_inode; struct nfs_pgio_mirror* pg_mirrors; TYPE_1__* pg_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  wsize; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* pg_cleanup ) (struct nfs_pageio_descriptor*) ;} ;

/* Variables and functions */
 TYPE_2__* NFS_SERVER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_pageio_stop_mirroring (struct nfs_pageio_descriptor*) ; 
 TYPE_1__ nfs_pgio_rw_ops ; 
 int /*<<< orphan*/  stub1 (struct nfs_pageio_descriptor*) ; 

void nfs_pageio_reset_write_mds(struct nfs_pageio_descriptor *pgio)
{
	struct nfs_pgio_mirror *mirror;

	if (pgio->pg_ops && pgio->pg_ops->pg_cleanup)
		pgio->pg_ops->pg_cleanup(pgio);

	pgio->pg_ops = &nfs_pgio_rw_ops;

	nfs_pageio_stop_mirroring(pgio);

	mirror = &pgio->pg_mirrors[0];
	mirror->pg_bsize = NFS_SERVER(pgio->pg_inode)->wsize;
}