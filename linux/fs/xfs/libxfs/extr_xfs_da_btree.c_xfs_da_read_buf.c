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
struct xfs_buf_ops {int dummy; } ;
struct xfs_buf_map {int dummy; } ;
struct xfs_buf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  m_ddev_targp; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_ATTR_BTREE_REF ; 
 int XFS_ATTR_FORK ; 
 int /*<<< orphan*/  XFS_DIR_BTREE_REF ; 
 int /*<<< orphan*/  kmem_free (struct xfs_buf_map*) ; 
 int /*<<< orphan*/  xfs_buf_set_ref (struct xfs_buf*,int /*<<< orphan*/ ) ; 
 int xfs_dabuf_map (struct xfs_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct xfs_buf_map**,int*) ; 
 int xfs_trans_read_buf_map (TYPE_1__*,struct xfs_trans*,int /*<<< orphan*/ ,struct xfs_buf_map*,int,int /*<<< orphan*/ ,struct xfs_buf**,struct xfs_buf_ops const*) ; 

int
xfs_da_read_buf(
	struct xfs_trans	*trans,
	struct xfs_inode	*dp,
	xfs_dablk_t		bno,
	xfs_daddr_t		mappedbno,
	struct xfs_buf		**bpp,
	int			whichfork,
	const struct xfs_buf_ops *ops)
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

	error = xfs_trans_read_buf_map(dp->i_mount, trans,
					dp->i_mount->m_ddev_targp,
					mapp, nmap, 0, &bp, ops);
	if (error)
		goto out_free;

	if (whichfork == XFS_ATTR_FORK)
		xfs_buf_set_ref(bp, XFS_ATTR_BTREE_REF);
	else
		xfs_buf_set_ref(bp, XFS_DIR_BTREE_REF);
	*bpp = bp;
out_free:
	if (mapp != &map)
		kmem_free(mapp);

	return error;
}