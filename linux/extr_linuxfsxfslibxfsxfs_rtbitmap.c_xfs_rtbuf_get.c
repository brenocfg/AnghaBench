#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
typedef  int /*<<< orphan*/  xfs_rtblock_t ;
struct TYPE_8__ {int /*<<< orphan*/  m_bsize; int /*<<< orphan*/  m_ddev_targp; int /*<<< orphan*/ * m_rbmip; int /*<<< orphan*/ * m_rsumip; } ;
typedef  TYPE_1__ xfs_mount_t ;
typedef  int /*<<< orphan*/  xfs_inode_t ;
typedef  int /*<<< orphan*/  xfs_buf_t ;
struct TYPE_9__ {scalar_t__ br_startblock; } ;
typedef  TYPE_2__ xfs_bmbt_irec_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int EFSCORRUPTED ; 
 scalar_t__ NULLFSBLOCK ; 
 int /*<<< orphan*/  XFS_BLFT_RTBITMAP_BUF ; 
 int /*<<< orphan*/  XFS_BLFT_RTSUMMARY_BUF ; 
 int /*<<< orphan*/  XFS_DATA_FORK ; 
 int /*<<< orphan*/  XFS_FSB_TO_DADDR (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  xfs_bmap_is_real_extent (TYPE_2__*) ; 
 int xfs_bmapi_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,TYPE_2__*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_rtbuf_ops ; 
 int /*<<< orphan*/  xfs_trans_buf_set_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int xfs_trans_read_buf (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

int
xfs_rtbuf_get(
	xfs_mount_t	*mp,		/* file system mount structure */
	xfs_trans_t	*tp,		/* transaction pointer */
	xfs_rtblock_t	block,		/* block number in bitmap or summary */
	int		issum,		/* is summary not bitmap */
	xfs_buf_t	**bpp)		/* output: buffer for the block */
{
	xfs_buf_t	*bp;		/* block buffer, result */
	xfs_inode_t	*ip;		/* bitmap or summary inode */
	xfs_bmbt_irec_t	map;
	int		nmap = 1;
	int		error;		/* error value */

	ip = issum ? mp->m_rsumip : mp->m_rbmip;

	error = xfs_bmapi_read(ip, block, 1, &map, &nmap, XFS_DATA_FORK);
	if (error)
		return error;

	if (nmap == 0 || !xfs_bmap_is_real_extent(&map))
		return -EFSCORRUPTED;

	ASSERT(map.br_startblock != NULLFSBLOCK);
	error = xfs_trans_read_buf(mp, tp, mp->m_ddev_targp,
				   XFS_FSB_TO_DADDR(mp, map.br_startblock),
				   mp->m_bsize, 0, &bp, &xfs_rtbuf_ops);
	if (error)
		return error;

	xfs_trans_buf_set_type(tp, bp, issum ? XFS_BLFT_RTSUMMARY_BUF
					     : XFS_BLFT_RTBITMAP_BUF);
	*bpp = bp;
	return 0;
}