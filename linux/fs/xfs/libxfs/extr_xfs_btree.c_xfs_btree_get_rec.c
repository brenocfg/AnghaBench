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
typedef  union xfs_btree_rec {int dummy; } xfs_btree_rec ;
struct xfs_buf {int dummy; } ;
struct xfs_btree_cur {int* bc_ptrs; } ;
struct xfs_btree_block {int dummy; } ;

/* Variables and functions */
 int xfs_btree_check_block (struct xfs_btree_cur*,struct xfs_btree_block*,int /*<<< orphan*/ ,struct xfs_buf*) ; 
 struct xfs_btree_block* xfs_btree_get_block (struct xfs_btree_cur*,int /*<<< orphan*/ ,struct xfs_buf**) ; 
 int xfs_btree_get_numrecs (struct xfs_btree_block*) ; 
 union xfs_btree_rec* xfs_btree_rec_addr (struct xfs_btree_cur*,int,struct xfs_btree_block*) ; 

int					/* error */
xfs_btree_get_rec(
	struct xfs_btree_cur	*cur,	/* btree cursor */
	union xfs_btree_rec	**recp,	/* output: btree record */
	int			*stat)	/* output: success/failure */
{
	struct xfs_btree_block	*block;	/* btree block */
	struct xfs_buf		*bp;	/* buffer pointer */
	int			ptr;	/* record number */
#ifdef DEBUG
	int			error;	/* error return value */
#endif

	ptr = cur->bc_ptrs[0];
	block = xfs_btree_get_block(cur, 0, &bp);

#ifdef DEBUG
	error = xfs_btree_check_block(cur, block, 0, bp);
	if (error)
		return error;
#endif

	/*
	 * Off the right end or left end, return failure.
	 */
	if (ptr > xfs_btree_get_numrecs(block) || ptr <= 0) {
		*stat = 0;
		return 0;
	}

	/*
	 * Point to the record and extract its data.
	 */
	*recp = xfs_btree_rec_addr(cur, ptr, block);
	*stat = 1;
	return 0;
}