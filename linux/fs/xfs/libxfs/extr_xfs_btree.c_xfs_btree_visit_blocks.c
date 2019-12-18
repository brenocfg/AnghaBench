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
typedef  int /*<<< orphan*/  xfs_btree_visit_blocks_fn ;
typedef  union xfs_btree_ptr {int dummy; } xfs_btree_ptr ;
struct xfs_btree_cur {int bc_nlevels; TYPE_1__* bc_ops; } ;
struct xfs_btree_block {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* init_ptr_from_cur ) (struct xfs_btree_cur*,union xfs_btree_ptr*) ;} ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  stub1 (struct xfs_btree_cur*,union xfs_btree_ptr*) ; 
 int /*<<< orphan*/  xfs_btree_copy_ptrs (struct xfs_btree_cur*,union xfs_btree_ptr*,union xfs_btree_ptr*,int) ; 
 int xfs_btree_lookup_get_block (struct xfs_btree_cur*,int,union xfs_btree_ptr*,struct xfs_btree_block**) ; 
 union xfs_btree_ptr* xfs_btree_ptr_addr (struct xfs_btree_cur*,int,struct xfs_btree_block*) ; 
 int /*<<< orphan*/  xfs_btree_readahead_ptr (struct xfs_btree_cur*,union xfs_btree_ptr*,int) ; 
 int xfs_btree_visit_block (struct xfs_btree_cur*,int,int /*<<< orphan*/ ,void*) ; 

int
xfs_btree_visit_blocks(
	struct xfs_btree_cur		*cur,
	xfs_btree_visit_blocks_fn	fn,
	void				*data)
{
	union xfs_btree_ptr		lptr;
	int				level;
	struct xfs_btree_block		*block = NULL;
	int				error = 0;

	cur->bc_ops->init_ptr_from_cur(cur, &lptr);

	/* for each level */
	for (level = cur->bc_nlevels - 1; level >= 0; level--) {
		/* grab the left hand block */
		error = xfs_btree_lookup_get_block(cur, level, &lptr, &block);
		if (error)
			return error;

		/* readahead the left most block for the next level down */
		if (level > 0) {
			union xfs_btree_ptr     *ptr;

			ptr = xfs_btree_ptr_addr(cur, 1, block);
			xfs_btree_readahead_ptr(cur, ptr, 1);

			/* save for the next iteration of the loop */
			xfs_btree_copy_ptrs(cur, &lptr, ptr, 1);
		}

		/* for each buffer in the level */
		do {
			error = xfs_btree_visit_block(cur, level, fn, data);
		} while (!error);

		if (error != -ENOENT)
			return error;
	}

	return 0;
}