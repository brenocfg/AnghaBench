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
struct xfs_mount {int dummy; } ;
struct xfs_bulkstat {int bs_projectid; int /*<<< orphan*/  bs_aextents; int /*<<< orphan*/  bs_cowextsize_blks; int /*<<< orphan*/  bs_checked; int /*<<< orphan*/  bs_sick; int /*<<< orphan*/  bs_forkoff; int /*<<< orphan*/  bs_gen; int /*<<< orphan*/  bs_extents; int /*<<< orphan*/  bs_extsize_blks; int /*<<< orphan*/  bs_xflags; int /*<<< orphan*/  bs_blocks; int /*<<< orphan*/  bs_ctime_nsec; int /*<<< orphan*/  bs_mtime_nsec; int /*<<< orphan*/  bs_atime_nsec; int /*<<< orphan*/  bs_ctime; int /*<<< orphan*/  bs_mtime; int /*<<< orphan*/  bs_atime; int /*<<< orphan*/  bs_size; int /*<<< orphan*/  bs_blksize; int /*<<< orphan*/  bs_rdev; int /*<<< orphan*/  bs_gid; int /*<<< orphan*/  bs_uid; int /*<<< orphan*/  bs_nlink; int /*<<< orphan*/  bs_mode; int /*<<< orphan*/  bs_ino; } ;
struct TYPE_6__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_5__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_4__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct xfs_bstat {int bs_projid_lo; int bs_projid_hi; int /*<<< orphan*/  bs_aextents; scalar_t__ bs_dmstate; scalar_t__ bs_dmevmask; void* bs_cowextsize; int /*<<< orphan*/  bs_checked; int /*<<< orphan*/  bs_sick; int /*<<< orphan*/  bs_forkoff; int /*<<< orphan*/  bs_gen; int /*<<< orphan*/  bs_extents; void* bs_extsize; int /*<<< orphan*/  bs_xflags; int /*<<< orphan*/  bs_blocks; TYPE_3__ bs_ctime; TYPE_2__ bs_mtime; TYPE_1__ bs_atime; int /*<<< orphan*/  bs_size; int /*<<< orphan*/  bs_blksize; int /*<<< orphan*/  bs_rdev; int /*<<< orphan*/  bs_gid; int /*<<< orphan*/  bs_uid; int /*<<< orphan*/  bs_nlink; int /*<<< orphan*/  bs_mode; int /*<<< orphan*/  bs_ino; } ;

/* Variables and functions */
 void* XFS_FSB_TO_B (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct xfs_bstat*,int /*<<< orphan*/ ,int) ; 

void
xfs_bulkstat_to_bstat(
	struct xfs_mount		*mp,
	struct xfs_bstat		*bs1,
	const struct xfs_bulkstat	*bstat)
{
	/* memset is needed here because of padding holes in the structure. */
	memset(bs1, 0, sizeof(struct xfs_bstat));
	bs1->bs_ino = bstat->bs_ino;
	bs1->bs_mode = bstat->bs_mode;
	bs1->bs_nlink = bstat->bs_nlink;
	bs1->bs_uid = bstat->bs_uid;
	bs1->bs_gid = bstat->bs_gid;
	bs1->bs_rdev = bstat->bs_rdev;
	bs1->bs_blksize = bstat->bs_blksize;
	bs1->bs_size = bstat->bs_size;
	bs1->bs_atime.tv_sec = bstat->bs_atime;
	bs1->bs_mtime.tv_sec = bstat->bs_mtime;
	bs1->bs_ctime.tv_sec = bstat->bs_ctime;
	bs1->bs_atime.tv_nsec = bstat->bs_atime_nsec;
	bs1->bs_mtime.tv_nsec = bstat->bs_mtime_nsec;
	bs1->bs_ctime.tv_nsec = bstat->bs_ctime_nsec;
	bs1->bs_blocks = bstat->bs_blocks;
	bs1->bs_xflags = bstat->bs_xflags;
	bs1->bs_extsize = XFS_FSB_TO_B(mp, bstat->bs_extsize_blks);
	bs1->bs_extents = bstat->bs_extents;
	bs1->bs_gen = bstat->bs_gen;
	bs1->bs_projid_lo = bstat->bs_projectid & 0xFFFF;
	bs1->bs_forkoff = bstat->bs_forkoff;
	bs1->bs_projid_hi = bstat->bs_projectid >> 16;
	bs1->bs_sick = bstat->bs_sick;
	bs1->bs_checked = bstat->bs_checked;
	bs1->bs_cowextsize = XFS_FSB_TO_B(mp, bstat->bs_cowextsize_blks);
	bs1->bs_dmevmask = 0;
	bs1->bs_dmstate = 0;
	bs1->bs_aextents = bstat->bs_aextents;
}