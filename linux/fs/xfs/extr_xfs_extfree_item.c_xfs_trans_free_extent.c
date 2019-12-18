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
typedef  int /*<<< orphan*/  xfs_fsblock_t ;
typedef  int /*<<< orphan*/  xfs_extlen_t ;
typedef  int /*<<< orphan*/  xfs_agnumber_t ;
typedef  int /*<<< orphan*/  xfs_agblock_t ;
typedef  size_t uint ;
struct xfs_trans {int /*<<< orphan*/  t_flags; struct xfs_mount* t_mountp; } ;
struct xfs_owner_info {int dummy; } ;
struct xfs_mount {int dummy; } ;
struct xfs_extent {int /*<<< orphan*/  ext_len; int /*<<< orphan*/  ext_start; } ;
struct TYPE_4__ {size_t efd_nextents; struct xfs_extent* efd_extents; } ;
struct TYPE_3__ {int /*<<< orphan*/  li_flags; } ;
struct xfs_efd_log_item {size_t efd_next_extent; TYPE_2__ efd_format; TYPE_1__ efd_item; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  XFS_AG_RESV_NONE ; 
 int /*<<< orphan*/  XFS_FSB_TO_AGBNO (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_FSB_TO_AGNO (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_LI_DIRTY ; 
 int /*<<< orphan*/  XFS_TRANS_DIRTY ; 
 int __xfs_free_extent (struct xfs_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_owner_info const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xfs_bmap_free_deferred (struct xfs_mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xfs_trans_free_extent(
	struct xfs_trans		*tp,
	struct xfs_efd_log_item		*efdp,
	xfs_fsblock_t			start_block,
	xfs_extlen_t			ext_len,
	const struct xfs_owner_info	*oinfo,
	bool				skip_discard)
{
	struct xfs_mount		*mp = tp->t_mountp;
	struct xfs_extent		*extp;
	uint				next_extent;
	xfs_agnumber_t			agno = XFS_FSB_TO_AGNO(mp, start_block);
	xfs_agblock_t			agbno = XFS_FSB_TO_AGBNO(mp,
								start_block);
	int				error;

	trace_xfs_bmap_free_deferred(tp->t_mountp, agno, 0, agbno, ext_len);

	error = __xfs_free_extent(tp, start_block, ext_len,
				  oinfo, XFS_AG_RESV_NONE, skip_discard);
	/*
	 * Mark the transaction dirty, even on error. This ensures the
	 * transaction is aborted, which:
	 *
	 * 1.) releases the EFI and frees the EFD
	 * 2.) shuts down the filesystem
	 */
	tp->t_flags |= XFS_TRANS_DIRTY;
	set_bit(XFS_LI_DIRTY, &efdp->efd_item.li_flags);

	next_extent = efdp->efd_next_extent;
	ASSERT(next_extent < efdp->efd_format.efd_nextents);
	extp = &(efdp->efd_format.efd_extents[next_extent]);
	extp->ext_start = start_block;
	extp->ext_len = ext_len;
	efdp->efd_next_extent++;

	return error;
}