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
typedef  union xfs_btree_rec {int dummy; } xfs_btree_rec ;
typedef  union xfs_btree_ptr {int dummy; } xfs_btree_ptr ;
typedef  union xfs_btree_key {int dummy; } xfs_btree_key ;
struct xfs_btree_cur {int /*<<< orphan*/  bc_nlevels; TYPE_1__* bc_ops; int /*<<< orphan*/  bc_mp; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* update_cursor ) (struct xfs_btree_cur*,struct xfs_btree_cur*) ;int /*<<< orphan*/  (* init_key_from_rec ) (union xfs_btree_key*,union xfs_btree_rec*) ;int /*<<< orphan*/  (* init_rec_from_cur ) (struct xfs_btree_cur*,union xfs_btree_rec*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_BTREE_ERROR ; 
 int /*<<< orphan*/  XFS_BTREE_NOERROR ; 
 int /*<<< orphan*/  XFS_WANT_CORRUPTED_GOTO (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error0 ; 
 int /*<<< orphan*/  stub1 (struct xfs_btree_cur*,union xfs_btree_rec*) ; 
 int /*<<< orphan*/  stub2 (union xfs_btree_key*,union xfs_btree_rec*) ; 
 int /*<<< orphan*/  stub3 (struct xfs_btree_cur*,struct xfs_btree_cur*) ; 
 int /*<<< orphan*/  xfs_btree_del_cursor (struct xfs_btree_cur*,int /*<<< orphan*/ ) ; 
 int xfs_btree_insrec (struct xfs_btree_cur*,int,union xfs_btree_ptr*,union xfs_btree_rec*,union xfs_btree_key*,struct xfs_btree_cur**,int*) ; 
 scalar_t__ xfs_btree_ptr_is_null (struct xfs_btree_cur*,union xfs_btree_ptr*) ; 
 int /*<<< orphan*/  xfs_btree_set_ptr_null (struct xfs_btree_cur*,union xfs_btree_ptr*) ; 

int
xfs_btree_insert(
	struct xfs_btree_cur	*cur,
	int			*stat)
{
	int			error;	/* error return value */
	int			i;	/* result value, 0 for failure */
	int			level;	/* current level number in btree */
	union xfs_btree_ptr	nptr;	/* new block number (split result) */
	struct xfs_btree_cur	*ncur;	/* new cursor (split result) */
	struct xfs_btree_cur	*pcur;	/* previous level's cursor */
	union xfs_btree_key	bkey;	/* key of block to insert */
	union xfs_btree_key	*key;
	union xfs_btree_rec	rec;	/* record to insert */

	level = 0;
	ncur = NULL;
	pcur = cur;
	key = &bkey;

	xfs_btree_set_ptr_null(cur, &nptr);

	/* Make a key out of the record data to be inserted, and save it. */
	cur->bc_ops->init_rec_from_cur(cur, &rec);
	cur->bc_ops->init_key_from_rec(key, &rec);

	/*
	 * Loop going up the tree, starting at the leaf level.
	 * Stop when we don't get a split block, that must mean that
	 * the insert is finished with this level.
	 */
	do {
		/*
		 * Insert nrec/nptr into this level of the tree.
		 * Note if we fail, nptr will be null.
		 */
		error = xfs_btree_insrec(pcur, level, &nptr, &rec, key,
				&ncur, &i);
		if (error) {
			if (pcur != cur)
				xfs_btree_del_cursor(pcur, XFS_BTREE_ERROR);
			goto error0;
		}

		XFS_WANT_CORRUPTED_GOTO(cur->bc_mp, i == 1, error0);
		level++;

		/*
		 * See if the cursor we just used is trash.
		 * Can't trash the caller's cursor, but otherwise we should
		 * if ncur is a new cursor or we're about to be done.
		 */
		if (pcur != cur &&
		    (ncur || xfs_btree_ptr_is_null(cur, &nptr))) {
			/* Save the state from the cursor before we trash it */
			if (cur->bc_ops->update_cursor)
				cur->bc_ops->update_cursor(pcur, cur);
			cur->bc_nlevels = pcur->bc_nlevels;
			xfs_btree_del_cursor(pcur, XFS_BTREE_NOERROR);
		}
		/* If we got a new cursor, switch to it. */
		if (ncur) {
			pcur = ncur;
			ncur = NULL;
		}
	} while (!xfs_btree_ptr_is_null(cur, &nptr));

	*stat = i;
	return 0;
error0:
	return error;
}