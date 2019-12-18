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
struct rpc_call_ops {int dummy; } ;
struct pnfs_layout_segment {int dummy; } ;
struct nfs_pgio_mirror {int pg_recoalesce; int /*<<< orphan*/  pg_list; } ;
struct nfs_pgio_header {TYPE_1__* mds_ops; int /*<<< orphan*/  pages; int /*<<< orphan*/  flags; } ;
struct nfs_pageio_descriptor {struct pnfs_layout_segment* pg_lseg; struct rpc_call_ops* pg_rpc_callops; } ;
typedef  enum pnfs_try_status { ____Placeholder_pnfs_try_status } pnfs_try_status ;
struct TYPE_2__ {int /*<<< orphan*/  (* rpc_release ) (struct nfs_pgio_header*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_IOHDR_REDO ; 
#define  PNFS_ATTEMPTED 130 
#define  PNFS_NOT_ATTEMPTED 129 
#define  PNFS_TRY_AGAIN 128 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct nfs_pgio_mirror* nfs_pgio_current_mirror (struct nfs_pageio_descriptor*) ; 
 int pnfs_try_to_write_data (struct nfs_pgio_header*,struct rpc_call_ops const*,struct pnfs_layout_segment*,int) ; 
 int /*<<< orphan*/  pnfs_write_through_mds (struct nfs_pageio_descriptor*,struct nfs_pgio_header*) ; 
 int /*<<< orphan*/  stub1 (struct nfs_pgio_header*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pnfs_do_write(struct nfs_pageio_descriptor *desc,
	      struct nfs_pgio_header *hdr, int how)
{
	const struct rpc_call_ops *call_ops = desc->pg_rpc_callops;
	struct pnfs_layout_segment *lseg = desc->pg_lseg;
	enum pnfs_try_status trypnfs;

	trypnfs = pnfs_try_to_write_data(hdr, call_ops, lseg, how);
	switch (trypnfs) {
	case PNFS_NOT_ATTEMPTED:
		pnfs_write_through_mds(desc, hdr);
	case PNFS_ATTEMPTED:
		break;
	case PNFS_TRY_AGAIN:
		/* cleanup hdr and prepare to redo pnfs */
		if (!test_and_set_bit(NFS_IOHDR_REDO, &hdr->flags)) {
			struct nfs_pgio_mirror *mirror = nfs_pgio_current_mirror(desc);
			list_splice_init(&hdr->pages, &mirror->pg_list);
			mirror->pg_recoalesce = 1;
		}
		hdr->mds_ops->rpc_release(hdr);
	}
}