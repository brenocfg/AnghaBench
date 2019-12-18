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
typedef  int /*<<< orphan*/  xfs_btnum_t ;
typedef  int /*<<< orphan*/  xfs_agnumber_t ;
struct xfs_trans {int dummy; } ;
struct xfs_mount {int dummy; } ;
struct xfs_buf {int dummy; } ;
struct xfs_btree_cur {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int xfs_ialloc_read_agi (struct xfs_mount*,struct xfs_trans*,int /*<<< orphan*/ ,struct xfs_buf**) ; 
 struct xfs_btree_cur* xfs_inobt_init_cursor (struct xfs_mount*,struct xfs_trans*,struct xfs_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_brelse (struct xfs_trans*,struct xfs_buf*) ; 

int
xfs_inobt_cur(
	struct xfs_mount	*mp,
	struct xfs_trans	*tp,
	xfs_agnumber_t		agno,
	xfs_btnum_t		which,
	struct xfs_btree_cur	**curpp,
	struct xfs_buf		**agi_bpp)
{
	struct xfs_btree_cur	*cur;
	int			error;

	ASSERT(*agi_bpp == NULL);
	ASSERT(*curpp == NULL);

	error = xfs_ialloc_read_agi(mp, tp, agno, agi_bpp);
	if (error)
		return error;

	cur = xfs_inobt_init_cursor(mp, tp, *agi_bpp, agno, which);
	if (!cur) {
		xfs_trans_brelse(tp, *agi_bpp);
		*agi_bpp = NULL;
		return -ENOMEM;
	}
	*curpp = cur;
	return 0;
}