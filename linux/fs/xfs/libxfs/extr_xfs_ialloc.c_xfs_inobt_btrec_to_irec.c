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
struct TYPE_6__ {int /*<<< orphan*/  ir_freecount; } ;
struct TYPE_5__ {void* ir_freecount; int /*<<< orphan*/  ir_count; int /*<<< orphan*/  ir_holemask; } ;
struct TYPE_7__ {TYPE_2__ f; TYPE_1__ sp; } ;
struct TYPE_8__ {int /*<<< orphan*/  ir_free; TYPE_3__ ir_u; int /*<<< orphan*/  ir_startino; } ;
union xfs_btree_rec {TYPE_4__ inobt; } ;
struct xfs_mount {int /*<<< orphan*/  m_sb; } ;
struct xfs_inobt_rec_incore {int /*<<< orphan*/  ir_free; void* ir_freecount; int /*<<< orphan*/  ir_count; int /*<<< orphan*/  ir_holemask; void* ir_startino; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_INOBT_HOLEMASK_FULL ; 
 int /*<<< orphan*/  XFS_INODES_PER_CHUNK ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ xfs_sb_version_hassparseinodes (int /*<<< orphan*/ *) ; 

void
xfs_inobt_btrec_to_irec(
	struct xfs_mount		*mp,
	union xfs_btree_rec		*rec,
	struct xfs_inobt_rec_incore	*irec)
{
	irec->ir_startino = be32_to_cpu(rec->inobt.ir_startino);
	if (xfs_sb_version_hassparseinodes(&mp->m_sb)) {
		irec->ir_holemask = be16_to_cpu(rec->inobt.ir_u.sp.ir_holemask);
		irec->ir_count = rec->inobt.ir_u.sp.ir_count;
		irec->ir_freecount = rec->inobt.ir_u.sp.ir_freecount;
	} else {
		/*
		 * ir_holemask/ir_count not supported on-disk. Fill in hardcoded
		 * values for full inode chunks.
		 */
		irec->ir_holemask = XFS_INOBT_HOLEMASK_FULL;
		irec->ir_count = XFS_INODES_PER_CHUNK;
		irec->ir_freecount =
				be32_to_cpu(rec->inobt.ir_u.f.ir_freecount);
	}
	irec->ir_free = be64_to_cpu(rec->inobt.ir_free);
}