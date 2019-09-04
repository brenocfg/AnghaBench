#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
struct TYPE_11__ {int /*<<< orphan*/  m_bsize; int /*<<< orphan*/  m_ddev_targp; } ;
typedef  TYPE_2__ xfs_mount_t ;
typedef  int /*<<< orphan*/  xfs_buf_t ;
struct TYPE_12__ {int bc_nlevels; int /*<<< orphan*/ ** bc_bufs; TYPE_1__* bc_ops; int /*<<< orphan*/ * bc_ra; int /*<<< orphan*/ * bc_ptrs; int /*<<< orphan*/  bc_rec; TYPE_2__* bc_mp; int /*<<< orphan*/ * bc_tp; } ;
typedef  TYPE_3__ xfs_btree_cur_t ;
struct TYPE_10__ {int /*<<< orphan*/  buf_ops; TYPE_3__* (* dup_cursor ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_BUF_ADDR (int /*<<< orphan*/ *) ; 
 TYPE_3__* stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  xfs_btree_del_cursor (TYPE_3__*,int) ; 
 int xfs_trans_read_buf (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

int					/* error */
xfs_btree_dup_cursor(
	xfs_btree_cur_t	*cur,		/* input cursor */
	xfs_btree_cur_t	**ncur)		/* output cursor */
{
	xfs_buf_t	*bp;		/* btree block's buffer pointer */
	int		error;		/* error return value */
	int		i;		/* level number of btree block */
	xfs_mount_t	*mp;		/* mount structure for filesystem */
	xfs_btree_cur_t	*new;		/* new cursor value */
	xfs_trans_t	*tp;		/* transaction pointer, can be NULL */

	tp = cur->bc_tp;
	mp = cur->bc_mp;

	/*
	 * Allocate a new cursor like the old one.
	 */
	new = cur->bc_ops->dup_cursor(cur);

	/*
	 * Copy the record currently in the cursor.
	 */
	new->bc_rec = cur->bc_rec;

	/*
	 * For each level current, re-get the buffer and copy the ptr value.
	 */
	for (i = 0; i < new->bc_nlevels; i++) {
		new->bc_ptrs[i] = cur->bc_ptrs[i];
		new->bc_ra[i] = cur->bc_ra[i];
		bp = cur->bc_bufs[i];
		if (bp) {
			error = xfs_trans_read_buf(mp, tp, mp->m_ddev_targp,
						   XFS_BUF_ADDR(bp), mp->m_bsize,
						   0, &bp,
						   cur->bc_ops->buf_ops);
			if (error) {
				xfs_btree_del_cursor(new, error);
				*ncur = NULL;
				return error;
			}
		}
		new->bc_bufs[i] = bp;
	}
	*ncur = new;
	return 0;
}