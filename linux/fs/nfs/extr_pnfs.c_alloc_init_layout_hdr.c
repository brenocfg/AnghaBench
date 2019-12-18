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
struct pnfs_layout_hdr {int plh_flags; int /*<<< orphan*/  plh_lc_cred; struct inode* plh_inode; int /*<<< orphan*/  plh_bulk_destroy; int /*<<< orphan*/  plh_return_segs; int /*<<< orphan*/  plh_segs; int /*<<< orphan*/  plh_layouts; int /*<<< orphan*/  plh_refcount; } ;
struct nfs_open_context {int /*<<< orphan*/  cred; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int NFS_LAYOUT_INVALID_STID ; 
 int /*<<< orphan*/  get_cred (int /*<<< orphan*/ ) ; 
 struct pnfs_layout_hdr* pnfs_alloc_layout_hdr (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct pnfs_layout_hdr *
alloc_init_layout_hdr(struct inode *ino,
		      struct nfs_open_context *ctx,
		      gfp_t gfp_flags)
{
	struct pnfs_layout_hdr *lo;

	lo = pnfs_alloc_layout_hdr(ino, gfp_flags);
	if (!lo)
		return NULL;
	refcount_set(&lo->plh_refcount, 1);
	INIT_LIST_HEAD(&lo->plh_layouts);
	INIT_LIST_HEAD(&lo->plh_segs);
	INIT_LIST_HEAD(&lo->plh_return_segs);
	INIT_LIST_HEAD(&lo->plh_bulk_destroy);
	lo->plh_inode = ino;
	lo->plh_lc_cred = get_cred(ctx->cred);
	lo->plh_flags |= 1 << NFS_LAYOUT_INVALID_STID;
	return lo;
}