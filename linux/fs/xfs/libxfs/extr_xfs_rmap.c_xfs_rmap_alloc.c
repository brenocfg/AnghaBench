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
typedef  int /*<<< orphan*/  xfs_extlen_t ;
typedef  int /*<<< orphan*/  xfs_agnumber_t ;
typedef  int /*<<< orphan*/  xfs_agblock_t ;
struct xfs_trans {struct xfs_mount* t_mountp; } ;
struct xfs_owner_info {int dummy; } ;
struct xfs_mount {int /*<<< orphan*/  m_sb; } ;
struct xfs_buf {int dummy; } ;
struct xfs_btree_cur {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfs_btree_del_cursor (struct xfs_btree_cur*,int) ; 
 int xfs_rmap_map (struct xfs_btree_cur*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct xfs_owner_info const*) ; 
 struct xfs_btree_cur* xfs_rmapbt_init_cursor (struct xfs_mount*,struct xfs_trans*,struct xfs_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_sb_version_hasrmapbt (int /*<<< orphan*/ *) ; 

int
xfs_rmap_alloc(
	struct xfs_trans		*tp,
	struct xfs_buf			*agbp,
	xfs_agnumber_t			agno,
	xfs_agblock_t			bno,
	xfs_extlen_t			len,
	const struct xfs_owner_info	*oinfo)
{
	struct xfs_mount		*mp = tp->t_mountp;
	struct xfs_btree_cur		*cur;
	int				error;

	if (!xfs_sb_version_hasrmapbt(&mp->m_sb))
		return 0;

	cur = xfs_rmapbt_init_cursor(mp, tp, agbp, agno);
	error = xfs_rmap_map(cur, bno, len, false, oinfo);

	xfs_btree_del_cursor(cur, error);
	return error;
}