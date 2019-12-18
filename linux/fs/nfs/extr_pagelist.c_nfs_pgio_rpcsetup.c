#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * verf; scalar_t__ eof; scalar_t__ count; int /*<<< orphan*/ * fattr; } ;
struct TYPE_5__ {unsigned int count; int /*<<< orphan*/  stable; int /*<<< orphan*/  lock_context; int /*<<< orphan*/  context; int /*<<< orphan*/  pages; int /*<<< orphan*/  pgbase; int /*<<< orphan*/  offset; int /*<<< orphan*/  fh; } ;
struct TYPE_4__ {int /*<<< orphan*/  pagevec; } ;
struct nfs_pgio_header {int /*<<< orphan*/  fattr; int /*<<< orphan*/  verf; TYPE_3__ res; TYPE_2__ args; TYPE_1__ page_array; int /*<<< orphan*/  mds_offset; int /*<<< orphan*/  inode; struct nfs_page* req; } ;
struct nfs_page {int /*<<< orphan*/  wb_lock_context; int /*<<< orphan*/  wb_pgbase; } ;
struct nfs_commit_info {int dummy; } ;

/* Variables and functions */
#define  FLUSH_COND_STABLE 128 
 int FLUSH_STABLE ; 
 int /*<<< orphan*/  NFS_FH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFS_FILE_SYNC ; 
 int /*<<< orphan*/  NFS_UNSTABLE ; 
 int /*<<< orphan*/  get_nfs_open_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_fattr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_req_openctx (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_reqs_to_commit (struct nfs_commit_info*) ; 
 int /*<<< orphan*/  req_offset (struct nfs_page*) ; 

__attribute__((used)) static void nfs_pgio_rpcsetup(struct nfs_pgio_header *hdr,
			      unsigned int count,
			      int how, struct nfs_commit_info *cinfo)
{
	struct nfs_page *req = hdr->req;

	/* Set up the RPC argument and reply structs
	 * NB: take care not to mess about with hdr->commit et al. */

	hdr->args.fh     = NFS_FH(hdr->inode);
	hdr->args.offset = req_offset(req);
	/* pnfs_set_layoutcommit needs this */
	hdr->mds_offset = hdr->args.offset;
	hdr->args.pgbase = req->wb_pgbase;
	hdr->args.pages  = hdr->page_array.pagevec;
	hdr->args.count  = count;
	hdr->args.context = get_nfs_open_context(nfs_req_openctx(req));
	hdr->args.lock_context = req->wb_lock_context;
	hdr->args.stable  = NFS_UNSTABLE;
	switch (how & (FLUSH_STABLE | FLUSH_COND_STABLE)) {
	case 0:
		break;
	case FLUSH_COND_STABLE:
		if (nfs_reqs_to_commit(cinfo))
			break;
		/* fall through */
	default:
		hdr->args.stable = NFS_FILE_SYNC;
	}

	hdr->res.fattr   = &hdr->fattr;
	hdr->res.count   = 0;
	hdr->res.eof     = 0;
	hdr->res.verf    = &hdr->verf;
	nfs_fattr_init(&hdr->fattr);
}