#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  next; } ;
struct nfs_pgio_mirror {int /*<<< orphan*/  pg_count; TYPE_1__ pg_list; } ;
struct nfs_pgio_header {void (* release ) (struct nfs_pgio_header*) ;int /*<<< orphan*/  pgio_mirror_idx; TYPE_3__* completion_ops; int /*<<< orphan*/  dreq; int /*<<< orphan*/  io_completion; int /*<<< orphan*/  good_bytes; TYPE_4__* req; int /*<<< orphan*/  io_start; int /*<<< orphan*/  cred; int /*<<< orphan*/  inode; } ;
struct nfs_pageio_descriptor {int /*<<< orphan*/  pg_mirror_idx; TYPE_3__* pg_completion_ops; int /*<<< orphan*/  pg_dreq; int /*<<< orphan*/  pg_io_completion; int /*<<< orphan*/  pg_inode; } ;
struct TYPE_9__ {TYPE_2__* wb_context; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* init_hdr ) (struct nfs_pgio_header*) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  cred; } ;

/* Variables and functions */
 TYPE_4__* nfs_list_entry (int /*<<< orphan*/ ) ; 
 struct nfs_pgio_mirror* nfs_pgio_current_mirror (struct nfs_pageio_descriptor*) ; 
 int /*<<< orphan*/  req_offset (TYPE_4__*) ; 
 int /*<<< orphan*/  stub1 (struct nfs_pgio_header*) ; 

void nfs_pgheader_init(struct nfs_pageio_descriptor *desc,
		       struct nfs_pgio_header *hdr,
		       void (*release)(struct nfs_pgio_header *hdr))
{
	struct nfs_pgio_mirror *mirror = nfs_pgio_current_mirror(desc);


	hdr->req = nfs_list_entry(mirror->pg_list.next);
	hdr->inode = desc->pg_inode;
	hdr->cred = hdr->req->wb_context->cred;
	hdr->io_start = req_offset(hdr->req);
	hdr->good_bytes = mirror->pg_count;
	hdr->io_completion = desc->pg_io_completion;
	hdr->dreq = desc->pg_dreq;
	hdr->release = release;
	hdr->completion_ops = desc->pg_completion_ops;
	if (hdr->completion_ops->init_hdr)
		hdr->completion_ops->init_hdr(hdr);

	hdr->pgio_mirror_idx = desc->pg_mirror_idx;
}