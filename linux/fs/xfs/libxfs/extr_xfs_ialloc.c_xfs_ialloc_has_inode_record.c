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
typedef  scalar_t__ xfs_agino_t ;
typedef  int uint16_t ;
struct xfs_inobt_rec_incore {scalar_t__ ir_startino; int ir_holemask; } ;
struct xfs_btree_cur {int dummy; } ;

/* Variables and functions */
 int XFS_INOBT_HOLEMASK_BITS ; 
 scalar_t__ XFS_INODES_PER_HOLEMASK_BIT ; 
 int /*<<< orphan*/  XFS_LOOKUP_LE ; 
 int xfs_btree_increment (struct xfs_btree_cur*,int /*<<< orphan*/ ,int*) ; 
 int xfs_inobt_get_rec (struct xfs_btree_cur*,struct xfs_inobt_rec_incore*,int*) ; 
 int xfs_inobt_lookup (struct xfs_btree_cur*,scalar_t__,int /*<<< orphan*/ ,int*) ; 

int
xfs_ialloc_has_inode_record(
	struct xfs_btree_cur	*cur,
	xfs_agino_t		low,
	xfs_agino_t		high,
	bool			*exists)
{
	struct xfs_inobt_rec_incore	irec;
	xfs_agino_t		agino;
	uint16_t		holemask;
	int			has_record;
	int			i;
	int			error;

	*exists = false;
	error = xfs_inobt_lookup(cur, low, XFS_LOOKUP_LE, &has_record);
	while (error == 0 && has_record) {
		error = xfs_inobt_get_rec(cur, &irec, &has_record);
		if (error || irec.ir_startino > high)
			break;

		agino = irec.ir_startino;
		holemask = irec.ir_holemask;
		for (i = 0; i < XFS_INOBT_HOLEMASK_BITS; holemask >>= 1,
				i++, agino += XFS_INODES_PER_HOLEMASK_BIT) {
			if (holemask & 1)
				continue;
			if (agino + XFS_INODES_PER_HOLEMASK_BIT > low &&
					agino <= high) {
				*exists = true;
				return 0;
			}
		}

		error = xfs_btree_increment(cur, 0, &has_record);
	}
	return error;
}