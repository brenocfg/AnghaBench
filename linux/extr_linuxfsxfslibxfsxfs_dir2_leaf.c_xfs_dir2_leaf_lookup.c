#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
struct TYPE_12__ {TYPE_1__* d_ops; } ;
typedef  TYPE_2__ xfs_inode_t ;
typedef  int /*<<< orphan*/  xfs_dir2_leaf_t ;
struct xfs_dir2_leaf_entry {int /*<<< orphan*/  address; } ;
typedef  struct xfs_dir2_leaf_entry xfs_dir2_leaf_entry_t ;
struct TYPE_13__ {int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; int /*<<< orphan*/  inumber; } ;
typedef  TYPE_3__ xfs_dir2_data_entry_t ;
struct TYPE_14__ {int /*<<< orphan*/  filetype; int /*<<< orphan*/  inumber; int /*<<< orphan*/  geo; TYPE_2__* dp; int /*<<< orphan*/ * trans; } ;
typedef  TYPE_4__ xfs_da_args_t ;
struct xfs_buf {int /*<<< orphan*/ * b_addr; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* data_get_ftype ) (TYPE_3__*) ;struct xfs_dir2_leaf_entry* (* leaf_ents_p ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 struct xfs_dir2_leaf_entry* stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 
 int /*<<< orphan*/  trace_xfs_dir2_leaf_lookup (TYPE_4__*) ; 
 int xfs_dir2_dataptr_to_off (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xfs_dir2_leaf_lookup_int (TYPE_4__*,struct xfs_buf**,int*,struct xfs_buf**) ; 
 int /*<<< orphan*/  xfs_dir3_leaf_check (TYPE_2__*,struct xfs_buf*) ; 
 int xfs_dir_cilookup_result (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_brelse (int /*<<< orphan*/ *,struct xfs_buf*) ; 

int
xfs_dir2_leaf_lookup(
	xfs_da_args_t		*args)		/* operation arguments */
{
	struct xfs_buf		*dbp;		/* data block buffer */
	xfs_dir2_data_entry_t	*dep;		/* data block entry */
	xfs_inode_t		*dp;		/* incore directory inode */
	int			error;		/* error return code */
	int			index;		/* found entry index */
	struct xfs_buf		*lbp;		/* leaf buffer */
	xfs_dir2_leaf_t		*leaf;		/* leaf structure */
	xfs_dir2_leaf_entry_t	*lep;		/* leaf entry */
	xfs_trans_t		*tp;		/* transaction pointer */
	struct xfs_dir2_leaf_entry *ents;

	trace_xfs_dir2_leaf_lookup(args);

	/*
	 * Look up name in the leaf block, returning both buffers and index.
	 */
	if ((error = xfs_dir2_leaf_lookup_int(args, &lbp, &index, &dbp))) {
		return error;
	}
	tp = args->trans;
	dp = args->dp;
	xfs_dir3_leaf_check(dp, lbp);
	leaf = lbp->b_addr;
	ents = dp->d_ops->leaf_ents_p(leaf);
	/*
	 * Get to the leaf entry and contained data entry address.
	 */
	lep = &ents[index];

	/*
	 * Point to the data entry.
	 */
	dep = (xfs_dir2_data_entry_t *)
	      ((char *)dbp->b_addr +
	       xfs_dir2_dataptr_to_off(args->geo, be32_to_cpu(lep->address)));
	/*
	 * Return the found inode number & CI name if appropriate
	 */
	args->inumber = be64_to_cpu(dep->inumber);
	args->filetype = dp->d_ops->data_get_ftype(dep);
	error = xfs_dir_cilookup_result(args, dep->name, dep->namelen);
	xfs_trans_brelse(tp, dbp);
	xfs_trans_brelse(tp, lbp);
	return error;
}