#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int xfs_agnumber_t ;
struct TYPE_2__ {int sb_agcount; } ;
struct xfs_mount {TYPE_1__ m_sb; int /*<<< orphan*/  m_ddev_targp; } ;
struct xfs_buf {int /*<<< orphan*/  b_length; int /*<<< orphan*/ * b_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBTOB (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_AG_DADDR (struct xfs_mount*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_BUF_TO_SBP (struct xfs_buf*) ; 
 int /*<<< orphan*/  XFS_FSS_TO_BB (struct xfs_mount*,int) ; 
 int /*<<< orphan*/  XFS_SB_DADDR ; 
 int /*<<< orphan*/  buffer_list ; 
 int /*<<< orphan*/  xfs_buf_delwri_queue (struct xfs_buf*,int /*<<< orphan*/ *) ; 
 int xfs_buf_delwri_submit (int /*<<< orphan*/ *) ; 
 struct xfs_buf* xfs_buf_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_buf_oneshot (struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_buf_relse (struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_buf_zero (struct xfs_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_sb_buf_ops ; 
 int /*<<< orphan*/  xfs_sb_to_disk (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  xfs_warn (struct xfs_mount*,char*,int,...) ; 

int
xfs_update_secondary_sbs(
	struct xfs_mount	*mp)
{
	xfs_agnumber_t		agno;
	int			saved_error = 0;
	int			error = 0;
	LIST_HEAD		(buffer_list);

	/* update secondary superblocks. */
	for (agno = 1; agno < mp->m_sb.sb_agcount; agno++) {
		struct xfs_buf		*bp;

		bp = xfs_buf_get(mp->m_ddev_targp,
				 XFS_AG_DADDR(mp, agno, XFS_SB_DADDR),
				 XFS_FSS_TO_BB(mp, 1));
		/*
		 * If we get an error reading or writing alternate superblocks,
		 * continue.  xfs_repair chooses the "best" superblock based
		 * on most matches; if we break early, we'll leave more
		 * superblocks un-updated than updated, and xfs_repair may
		 * pick them over the properly-updated primary.
		 */
		if (!bp) {
			xfs_warn(mp,
		"error allocating secondary superblock for ag %d",
				agno);
			if (!saved_error)
				saved_error = -ENOMEM;
			continue;
		}

		bp->b_ops = &xfs_sb_buf_ops;
		xfs_buf_oneshot(bp);
		xfs_buf_zero(bp, 0, BBTOB(bp->b_length));
		xfs_sb_to_disk(XFS_BUF_TO_SBP(bp), &mp->m_sb);
		xfs_buf_delwri_queue(bp, &buffer_list);
		xfs_buf_relse(bp);

		/* don't hold too many buffers at once */
		if (agno % 16)
			continue;

		error = xfs_buf_delwri_submit(&buffer_list);
		if (error) {
			xfs_warn(mp,
		"write error %d updating a secondary superblock near ag %d",
				error, agno);
			if (!saved_error)
				saved_error = error;
			continue;
		}
	}
	error = xfs_buf_delwri_submit(&buffer_list);
	if (error) {
		xfs_warn(mp,
		"write error %d updating a secondary superblock near ag %d",
			error, agno);
	}

	return saved_error ? saved_error : error;
}