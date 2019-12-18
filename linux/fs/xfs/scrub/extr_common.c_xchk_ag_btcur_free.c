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
struct xchk_ag {int /*<<< orphan*/ * cnt_cur; int /*<<< orphan*/ * bno_cur; int /*<<< orphan*/ * ino_cur; int /*<<< orphan*/ * fino_cur; int /*<<< orphan*/ * rmap_cur; int /*<<< orphan*/ * refc_cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_BTREE_ERROR ; 
 int /*<<< orphan*/  xfs_btree_del_cursor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
xchk_ag_btcur_free(
	struct xchk_ag		*sa)
{
	if (sa->refc_cur)
		xfs_btree_del_cursor(sa->refc_cur, XFS_BTREE_ERROR);
	if (sa->rmap_cur)
		xfs_btree_del_cursor(sa->rmap_cur, XFS_BTREE_ERROR);
	if (sa->fino_cur)
		xfs_btree_del_cursor(sa->fino_cur, XFS_BTREE_ERROR);
	if (sa->ino_cur)
		xfs_btree_del_cursor(sa->ino_cur, XFS_BTREE_ERROR);
	if (sa->cnt_cur)
		xfs_btree_del_cursor(sa->cnt_cur, XFS_BTREE_ERROR);
	if (sa->bno_cur)
		xfs_btree_del_cursor(sa->bno_cur, XFS_BTREE_ERROR);

	sa->refc_cur = NULL;
	sa->rmap_cur = NULL;
	sa->fino_cur = NULL;
	sa->ino_cur = NULL;
	sa->bno_cur = NULL;
	sa->cnt_cur = NULL;
}