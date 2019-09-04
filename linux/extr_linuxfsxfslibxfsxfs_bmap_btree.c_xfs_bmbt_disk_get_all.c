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
typedef  int uint64_t ;
struct xfs_bmbt_rec {int /*<<< orphan*/  l1; int /*<<< orphan*/  l0; } ;
struct xfs_bmbt_irec {int br_startoff; int br_startblock; int br_blockcount; int /*<<< orphan*/  br_state; } ;

/* Variables and functions */
 int BMBT_EXNTFLAG_BITLEN ; 
 int /*<<< orphan*/  XFS_EXT_NORM ; 
 int /*<<< orphan*/  XFS_EXT_UNWRITTEN ; 
 int get_unaligned_be64 (int /*<<< orphan*/ *) ; 
 int xfs_mask64lo (int) ; 

void
xfs_bmbt_disk_get_all(
	struct xfs_bmbt_rec	*rec,
	struct xfs_bmbt_irec	*irec)
{
	uint64_t		l0 = get_unaligned_be64(&rec->l0);
	uint64_t		l1 = get_unaligned_be64(&rec->l1);

	irec->br_startoff = (l0 & xfs_mask64lo(64 - BMBT_EXNTFLAG_BITLEN)) >> 9;
	irec->br_startblock = ((l0 & xfs_mask64lo(9)) << 43) | (l1 >> 21);
	irec->br_blockcount = l1 & xfs_mask64lo(21);
	if (l0 >> (64 - BMBT_EXNTFLAG_BITLEN))
		irec->br_state = XFS_EXT_UNWRITTEN;
	else
		irec->br_state = XFS_EXT_NORM;
}