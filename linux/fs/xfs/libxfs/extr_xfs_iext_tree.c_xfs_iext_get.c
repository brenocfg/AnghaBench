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
struct xfs_iext_rec {int lo; int hi; } ;
struct xfs_bmbt_irec {int br_startoff; int br_blockcount; int br_startblock; int /*<<< orphan*/  br_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_EXT_NORM ; 
 int /*<<< orphan*/  XFS_EXT_UNWRITTEN ; 
 int XFS_IEXT_LENGTH_MASK ; 
 int XFS_IEXT_STARTOFF_MASK ; 
 int xfs_mask64hi (int) ; 

__attribute__((used)) static void
xfs_iext_get(
	struct xfs_bmbt_irec	*irec,
	struct xfs_iext_rec	*rec)
{
	irec->br_startoff = rec->lo & XFS_IEXT_STARTOFF_MASK;
	irec->br_blockcount = rec->hi & XFS_IEXT_LENGTH_MASK;

	irec->br_startblock = rec->lo >> 54;
	irec->br_startblock |= (rec->hi & xfs_mask64hi(42)) >> (22 - 10);

	if (rec->hi & (1 << 21))
		irec->br_state = XFS_EXT_UNWRITTEN;
	else
		irec->br_state = XFS_EXT_NORM;
}