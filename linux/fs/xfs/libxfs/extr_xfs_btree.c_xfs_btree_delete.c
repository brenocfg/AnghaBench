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
struct xfs_btree_cur {int bc_flags; int bc_nlevels; scalar_t__* bc_ptrs; } ;

/* Variables and functions */
 int XFS_BTREE_OVERLAPPING ; 
 int xfs_btree_decrement (struct xfs_btree_cur*,int,int*) ; 
 int xfs_btree_delrec (struct xfs_btree_cur*,int,int*) ; 
 int xfs_btree_updkeys_force (struct xfs_btree_cur*,int /*<<< orphan*/ ) ; 

int					/* error */
xfs_btree_delete(
	struct xfs_btree_cur	*cur,
	int			*stat)	/* success/failure */
{
	int			error;	/* error return value */
	int			level;
	int			i;
	bool			joined = false;

	/*
	 * Go up the tree, starting at leaf level.
	 *
	 * If 2 is returned then a join was done; go to the next level.
	 * Otherwise we are done.
	 */
	for (level = 0, i = 2; i == 2; level++) {
		error = xfs_btree_delrec(cur, level, &i);
		if (error)
			goto error0;
		if (i == 2)
			joined = true;
	}

	/*
	 * If we combined blocks as part of deleting the record, delrec won't
	 * have updated the parent high keys so we have to do that here.
	 */
	if (joined && (cur->bc_flags & XFS_BTREE_OVERLAPPING)) {
		error = xfs_btree_updkeys_force(cur, 0);
		if (error)
			goto error0;
	}

	if (i == 0) {
		for (level = 1; level < cur->bc_nlevels; level++) {
			if (cur->bc_ptrs[level] == 0) {
				error = xfs_btree_decrement(cur, level, &i);
				if (error)
					goto error0;
				break;
			}
		}
	}

	*stat = i;
	return 0;
error0:
	return error;
}