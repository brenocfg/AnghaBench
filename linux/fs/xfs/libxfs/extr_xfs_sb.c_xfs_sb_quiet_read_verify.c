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
struct xfs_dsb {scalar_t__ sb_magicnum; } ;
struct xfs_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EWRONGFS ; 
 struct xfs_dsb* XFS_BUF_TO_SBP (struct xfs_buf*) ; 
 int /*<<< orphan*/  XFS_SB_MAGIC ; 
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_buf_ioerror (struct xfs_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_sb_read_verify (struct xfs_buf*) ; 

__attribute__((used)) static void
xfs_sb_quiet_read_verify(
	struct xfs_buf	*bp)
{
	struct xfs_dsb	*dsb = XFS_BUF_TO_SBP(bp);

	if (dsb->sb_magicnum == cpu_to_be32(XFS_SB_MAGIC)) {
		/* XFS filesystem, verify noisily! */
		xfs_sb_read_verify(bp);
		return;
	}
	/* quietly fail */
	xfs_buf_ioerror(bp, -EWRONGFS);
}