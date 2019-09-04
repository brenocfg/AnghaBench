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
struct pnfs_layout_hdr {struct inode* plh_inode; } ;
struct TYPE_4__ {int iomode; int /*<<< orphan*/  length; scalar_t__ offset; } ;
struct nfs4_layoutreturn_args {int /*<<< orphan*/  stateid; struct pnfs_layout_hdr* layout; TYPE_1__ range; struct inode* inode; int /*<<< orphan*/  layout_type; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  nfs4_stateid ;
typedef  enum pnfs_iomode { ____Placeholder_pnfs_iomode } pnfs_iomode ;
struct TYPE_6__ {TYPE_2__* pnfs_curr_ld; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4_MAX_UINT64 ; 
 TYPE_3__* NFS_SERVER (struct inode*) ; 
 int /*<<< orphan*/  nfs4_stateid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
pnfs_init_layoutreturn_args(struct nfs4_layoutreturn_args *args,
		struct pnfs_layout_hdr *lo,
		const nfs4_stateid *stateid,
		enum pnfs_iomode iomode)
{
	struct inode *inode = lo->plh_inode;

	args->layout_type = NFS_SERVER(inode)->pnfs_curr_ld->id;
	args->inode = inode;
	args->range.iomode = iomode;
	args->range.offset = 0;
	args->range.length = NFS4_MAX_UINT64;
	args->layout = lo;
	nfs4_stateid_copy(&args->stateid, stateid);
}