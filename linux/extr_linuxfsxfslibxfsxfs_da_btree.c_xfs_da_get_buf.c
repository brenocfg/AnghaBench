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
typedef  int /*<<< orphan*/  xfs_daddr_t ;
typedef  int /*<<< orphan*/  xfs_dablk_t ;
struct xfs_trans {int dummy; } ;
struct xfs_inode {TYPE_1__* i_mount; } ;
struct xfs_buf_map {int dummy; } ;
struct xfs_buf {int b_error; } ;
struct TYPE_2__ {int /*<<< orphan*/  m_ddev_targp; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  kmem_free (struct xfs_buf_map*) ; 
 int xfs_dabuf_map (struct xfs_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct xfs_buf_map**,int*) ; 
 int /*<<< orphan*/  xfs_trans_brelse (struct xfs_trans*,struct xfs_buf*) ; 
 struct xfs_buf* xfs_trans_get_buf_map (struct xfs_trans*,int /*<<< orphan*/ ,struct xfs_buf_map*,int,int /*<<< orphan*/ ) ; 

int
xfs_da_get_buf(
	struct xfs_trans	*trans,
	struct xfs_inode	*dp,
	xfs_dablk_t		bno,
	xfs_daddr_t		mappedbno,
	struct xfs_buf		**bpp,
	int			whichfork)
{
	struct xfs_buf		*bp;
	struct xfs_buf_map	map;
	struct xfs_buf_map	*mapp;
	int			nmap;
	int			error;

	*bpp = NULL;
	mapp = &map;
	nmap = 1;
	error = xfs_dabuf_map(dp, bno, mappedbno, whichfork,
				&mapp, &nmap);
	if (error) {
		/* mapping a hole is not an error, but we don't continue */
		if (error == -1)
			error = 0;
		goto out_free;
	}

	bp = xfs_trans_get_buf_map(trans, dp->i_mount->m_ddev_targp,
				    mapp, nmap, 0);
	error = bp ? bp->b_error : -EIO;
	if (error) {
		if (bp)
			xfs_trans_brelse(trans, bp);
		goto out_free;
	}

	*bpp = bp;

out_free:
	if (mapp != &map)
		kmem_free(mapp);

	return error;
}