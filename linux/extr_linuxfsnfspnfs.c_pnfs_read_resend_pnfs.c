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
struct TYPE_2__ {int /*<<< orphan*/  tk_status; } ;
struct nfs_pgio_header {TYPE_1__ task; int /*<<< orphan*/  completion_ops; int /*<<< orphan*/  inode; int /*<<< orphan*/ * lseg; int /*<<< orphan*/  flags; } ;
struct nfs_pageio_descriptor {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_IOHDR_REDO ; 
 int /*<<< orphan*/  nfs_pageio_init_read (struct nfs_pageio_descriptor*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_pageio_resend (struct nfs_pageio_descriptor*,struct nfs_pgio_header*) ; 
 int /*<<< orphan*/  pnfs_put_lseg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void pnfs_read_resend_pnfs(struct nfs_pgio_header *hdr)
{
	struct nfs_pageio_descriptor pgio;

	if (!test_and_set_bit(NFS_IOHDR_REDO, &hdr->flags)) {
		/* Prevent deadlocks with layoutreturn! */
		pnfs_put_lseg(hdr->lseg);
		hdr->lseg = NULL;

		nfs_pageio_init_read(&pgio, hdr->inode, false,
					hdr->completion_ops);
		hdr->task.tk_status = nfs_pageio_resend(&pgio, hdr);
	}
}