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
struct xfs_mount {int /*<<< orphan*/  m_sb; } ;
struct xfs_dsb {int sb_inprogress; } ;
struct xfs_buf {int dummy; } ;
struct aghdr_init_data {int dummy; } ;

/* Variables and functions */
 struct xfs_dsb* XFS_BUF_TO_SBP (struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_sb_to_disk (struct xfs_dsb*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xfs_sbblock_init(
	struct xfs_mount	*mp,
	struct xfs_buf		*bp,
	struct aghdr_init_data	*id)
{
	struct xfs_dsb		*dsb = XFS_BUF_TO_SBP(bp);

	xfs_sb_to_disk(dsb, &mp->m_sb);
	dsb->sb_inprogress = 1;
}