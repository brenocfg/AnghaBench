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
struct pnfs_layout_segment {int dummy; } ;
struct nfs_page {int dummy; } ;
struct nfs_open_context {int /*<<< orphan*/  cred; int /*<<< orphan*/  dentry; } ;
struct nfs_commit_info {int /*<<< orphan*/  dreq; int /*<<< orphan*/  completion_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/ * verf; int /*<<< orphan*/ * fattr; } ;
struct TYPE_3__ {scalar_t__ count; scalar_t__ offset; int /*<<< orphan*/  fh; } ;
struct nfs_commit_data {int /*<<< orphan*/  fattr; int /*<<< orphan*/  verf; TYPE_2__ res; int /*<<< orphan*/  context; TYPE_1__ args; struct inode* inode; int /*<<< orphan*/  dreq; int /*<<< orphan*/  completion_ops; int /*<<< orphan*/ * mds_ops; int /*<<< orphan*/  pages; int /*<<< orphan*/  lwb; struct pnfs_layout_segment* lseg; int /*<<< orphan*/  cred; } ;
struct list_head {int /*<<< orphan*/  next; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_FH (struct inode*) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_nfs_open_context (struct nfs_open_context*) ; 
 int /*<<< orphan*/  list_splice_init (struct list_head*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_commit_ops ; 
 int /*<<< orphan*/  nfs_fattr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_get_lwb (int /*<<< orphan*/ *) ; 
 struct nfs_page* nfs_list_entry (int /*<<< orphan*/ ) ; 
 struct nfs_open_context* nfs_req_openctx (struct nfs_page*) ; 

void nfs_init_commit(struct nfs_commit_data *data,
		     struct list_head *head,
		     struct pnfs_layout_segment *lseg,
		     struct nfs_commit_info *cinfo)
{
	struct nfs_page *first = nfs_list_entry(head->next);
	struct nfs_open_context *ctx = nfs_req_openctx(first);
	struct inode *inode = d_inode(ctx->dentry);

	/* Set up the RPC argument and reply structs
	 * NB: take care not to mess about with data->commit et al. */

	list_splice_init(head, &data->pages);

	data->inode	  = inode;
	data->cred	  = ctx->cred;
	data->lseg	  = lseg; /* reference transferred */
	/* only set lwb for pnfs commit */
	if (lseg)
		data->lwb = nfs_get_lwb(&data->pages);
	data->mds_ops     = &nfs_commit_ops;
	data->completion_ops = cinfo->completion_ops;
	data->dreq	  = cinfo->dreq;

	data->args.fh     = NFS_FH(data->inode);
	/* Note: we always request a commit of the entire inode */
	data->args.offset = 0;
	data->args.count  = 0;
	data->context     = get_nfs_open_context(ctx);
	data->res.fattr   = &data->fattr;
	data->res.verf    = &data->verf;
	nfs_fattr_init(&data->fattr);
}