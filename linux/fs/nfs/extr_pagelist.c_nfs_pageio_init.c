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
struct nfs_rw_ops {int dummy; } ;
struct nfs_pgio_completion_ops {int dummy; } ;
struct nfs_pageio_ops {int dummy; } ;
struct nfs_pageio_descriptor {int pg_ioflags; size_t pg_bsize; int pg_mirror_count; scalar_t__ pg_maxretrans; int /*<<< orphan*/ * pg_mirrors; int /*<<< orphan*/ * pg_mirrors_static; int /*<<< orphan*/ * pg_mirrors_dynamic; scalar_t__ pg_mirror_idx; int /*<<< orphan*/ * pg_dreq; int /*<<< orphan*/ * pg_io_completion; int /*<<< orphan*/ * pg_lseg; scalar_t__ pg_error; struct nfs_rw_ops const* pg_rw_ops; struct nfs_pgio_completion_ops const* pg_completion_ops; struct nfs_pageio_ops const* pg_ops; struct inode* pg_inode; scalar_t__ pg_moreio; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_pageio_mirror_init (int /*<<< orphan*/ *,size_t) ; 

void nfs_pageio_init(struct nfs_pageio_descriptor *desc,
		     struct inode *inode,
		     const struct nfs_pageio_ops *pg_ops,
		     const struct nfs_pgio_completion_ops *compl_ops,
		     const struct nfs_rw_ops *rw_ops,
		     size_t bsize,
		     int io_flags)
{
	desc->pg_moreio = 0;
	desc->pg_inode = inode;
	desc->pg_ops = pg_ops;
	desc->pg_completion_ops = compl_ops;
	desc->pg_rw_ops = rw_ops;
	desc->pg_ioflags = io_flags;
	desc->pg_error = 0;
	desc->pg_lseg = NULL;
	desc->pg_io_completion = NULL;
	desc->pg_dreq = NULL;
	desc->pg_bsize = bsize;

	desc->pg_mirror_count = 1;
	desc->pg_mirror_idx = 0;

	desc->pg_mirrors_dynamic = NULL;
	desc->pg_mirrors = desc->pg_mirrors_static;
	nfs_pageio_mirror_init(&desc->pg_mirrors[0], bsize);
	desc->pg_maxretrans = 0;
}