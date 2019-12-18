#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xfs_fsblock_t ;
struct TYPE_7__ {scalar_t__ ext_len; int /*<<< orphan*/  ext_start; } ;
typedef  TYPE_3__ xfs_extent_t ;
struct xfs_trans {int dummy; } ;
struct TYPE_5__ {scalar_t__ sb_dblocks; scalar_t__ sb_agblocks; } ;
struct xfs_mount {TYPE_1__ m_sb; } ;
struct TYPE_6__ {int efi_nextents; TYPE_3__* efi_extents; } ;
struct xfs_efi_log_item {int /*<<< orphan*/  efi_flags; TYPE_2__ efi_format; } ;
struct xfs_efd_log_item {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  tr_itruncate; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int EIO ; 
 TYPE_4__* M_RES (struct xfs_mount*) ; 
 scalar_t__ XFS_BB_TO_FSB (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_EFI_RECOVERED ; 
 int /*<<< orphan*/  XFS_FSB_TO_DADDR (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_RMAP_OINFO_ANY_OWNER ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_efi_release (struct xfs_efi_log_item*) ; 
 int xfs_trans_alloc (struct xfs_mount*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_trans**) ; 
 int /*<<< orphan*/  xfs_trans_cancel (struct xfs_trans*) ; 
 int xfs_trans_commit (struct xfs_trans*) ; 
 int xfs_trans_free_extent (struct xfs_trans*,struct xfs_efd_log_item*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 
 struct xfs_efd_log_item* xfs_trans_get_efd (struct xfs_trans*,struct xfs_efi_log_item*,int) ; 

int
xfs_efi_recover(
	struct xfs_mount	*mp,
	struct xfs_efi_log_item	*efip)
{
	struct xfs_efd_log_item	*efdp;
	struct xfs_trans	*tp;
	int			i;
	int			error = 0;
	xfs_extent_t		*extp;
	xfs_fsblock_t		startblock_fsb;

	ASSERT(!test_bit(XFS_EFI_RECOVERED, &efip->efi_flags));

	/*
	 * First check the validity of the extents described by the
	 * EFI.  If any are bad, then assume that all are bad and
	 * just toss the EFI.
	 */
	for (i = 0; i < efip->efi_format.efi_nextents; i++) {
		extp = &efip->efi_format.efi_extents[i];
		startblock_fsb = XFS_BB_TO_FSB(mp,
				   XFS_FSB_TO_DADDR(mp, extp->ext_start));
		if (startblock_fsb == 0 ||
		    extp->ext_len == 0 ||
		    startblock_fsb >= mp->m_sb.sb_dblocks ||
		    extp->ext_len >= mp->m_sb.sb_agblocks) {
			/*
			 * This will pull the EFI from the AIL and
			 * free the memory associated with it.
			 */
			set_bit(XFS_EFI_RECOVERED, &efip->efi_flags);
			xfs_efi_release(efip);
			return -EIO;
		}
	}

	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_itruncate, 0, 0, 0, &tp);
	if (error)
		return error;
	efdp = xfs_trans_get_efd(tp, efip, efip->efi_format.efi_nextents);

	for (i = 0; i < efip->efi_format.efi_nextents; i++) {
		extp = &efip->efi_format.efi_extents[i];
		error = xfs_trans_free_extent(tp, efdp, extp->ext_start,
					      extp->ext_len,
					      &XFS_RMAP_OINFO_ANY_OWNER, false);
		if (error)
			goto abort_error;

	}

	set_bit(XFS_EFI_RECOVERED, &efip->efi_flags);
	error = xfs_trans_commit(tp);
	return error;

abort_error:
	xfs_trans_cancel(tp);
	return error;
}