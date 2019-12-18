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
struct TYPE_4__ {TYPE_1__* context; } ;
struct nfs_pgio_header {TYPE_2__ args; int /*<<< orphan*/  completion_ops; int /*<<< orphan*/  inode; } ;
struct nfs_pageio_descriptor {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLUSH_STABLE ; 
 int /*<<< orphan*/  NFS_CONTEXT_RESEND_WRITES ; 
 int /*<<< orphan*/  nfs_pageio_init_write (struct nfs_pageio_descriptor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int nfs_pageio_resend (struct nfs_pageio_descriptor*,struct nfs_pgio_header*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int pnfs_write_done_resend_to_mds(struct nfs_pgio_header *hdr)
{
	struct nfs_pageio_descriptor pgio;

	/* Resend all requests through the MDS */
	nfs_pageio_init_write(&pgio, hdr->inode, FLUSH_STABLE, true,
			      hdr->completion_ops);
	set_bit(NFS_CONTEXT_RESEND_WRITES, &hdr->args.context->flags);
	return nfs_pageio_resend(&pgio, hdr);
}