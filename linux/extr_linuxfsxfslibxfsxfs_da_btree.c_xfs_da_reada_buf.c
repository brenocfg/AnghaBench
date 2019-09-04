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
struct xfs_inode {TYPE_1__* i_mount; } ;
struct xfs_buf_ops {int dummy; } ;
struct xfs_buf_map {int /*<<< orphan*/  bm_bn; } ;
struct TYPE_2__ {int /*<<< orphan*/  m_ddev_targp; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_free (struct xfs_buf_map*) ; 
 int /*<<< orphan*/  xfs_buf_readahead_map (int /*<<< orphan*/ ,struct xfs_buf_map*,int,struct xfs_buf_ops const*) ; 
 int xfs_dabuf_map (struct xfs_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct xfs_buf_map**,int*) ; 

int
xfs_da_reada_buf(
	struct xfs_inode	*dp,
	xfs_dablk_t		bno,
	xfs_daddr_t		mappedbno,
	int			whichfork,
	const struct xfs_buf_ops *ops)
{
	struct xfs_buf_map	map;
	struct xfs_buf_map	*mapp;
	int			nmap;
	int			error;

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

	mappedbno = mapp[0].bm_bn;
	xfs_buf_readahead_map(dp->i_mount->m_ddev_targp, mapp, nmap, ops);

out_free:
	if (mapp != &map)
		kmem_free(mapp);

	return error;
}