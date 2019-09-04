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
struct TYPE_4__ {size_t pglen; int /*<<< orphan*/  pages; } ;
struct TYPE_5__ {int /*<<< orphan*/  ctx; scalar_t__ inode; TYPE_1__ layout; } ;
struct nfs4_layoutget {TYPE_2__ args; int /*<<< orphan*/  cred; } ;
struct TYPE_6__ {int /*<<< orphan*/  layout; } ;

/* Variables and functions */
 TYPE_3__* NFS_I (scalar_t__) ; 
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  kfree (struct nfs4_layoutget*) ; 
 int /*<<< orphan*/  nfs4_free_pages (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  pnfs_put_layout_hdr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_nfs_open_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_rpccred (int /*<<< orphan*/ ) ; 

void pnfs_layoutget_free(struct nfs4_layoutget *lgp)
{
	size_t max_pages = lgp->args.layout.pglen / PAGE_SIZE;

	nfs4_free_pages(lgp->args.layout.pages, max_pages);
	if (lgp->args.inode)
		pnfs_put_layout_hdr(NFS_I(lgp->args.inode)->layout);
	put_rpccred(lgp->cred);
	put_nfs_open_context(lgp->args.ctx);
	kfree(lgp);
}