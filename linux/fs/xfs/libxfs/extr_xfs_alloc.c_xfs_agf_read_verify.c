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
typedef  int /*<<< orphan*/  xfs_failaddr_t ;
struct xfs_mount {int /*<<< orphan*/  m_sb; } ;
struct xfs_buf {struct xfs_mount* b_mount; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFSBADCRC ; 
 int /*<<< orphan*/  EFSCORRUPTED ; 
 int /*<<< orphan*/  XFS_AGF_CRC_OFF ; 
 int /*<<< orphan*/  XFS_ERRTAG_ALLOC_READ_AGF ; 
 scalar_t__ XFS_TEST_ERROR (int /*<<< orphan*/ ,struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __this_address ; 
 int /*<<< orphan*/  xfs_agf_verify (struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_buf_verify_cksum (struct xfs_buf*,int /*<<< orphan*/ ) ; 
 scalar_t__ xfs_sb_version_hascrc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_verifier_error (struct xfs_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xfs_agf_read_verify(
	struct xfs_buf	*bp)
{
	struct xfs_mount *mp = bp->b_mount;
	xfs_failaddr_t	fa;

	if (xfs_sb_version_hascrc(&mp->m_sb) &&
	    !xfs_buf_verify_cksum(bp, XFS_AGF_CRC_OFF))
		xfs_verifier_error(bp, -EFSBADCRC, __this_address);
	else {
		fa = xfs_agf_verify(bp);
		if (XFS_TEST_ERROR(fa, mp, XFS_ERRTAG_ALLOC_READ_AGF))
			xfs_verifier_error(bp, -EFSCORRUPTED, fa);
	}
}