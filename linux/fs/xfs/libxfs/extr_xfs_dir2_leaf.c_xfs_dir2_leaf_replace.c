#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
struct TYPE_13__ {TYPE_1__* d_ops; } ;
typedef  TYPE_2__ xfs_inode_t ;
typedef  int /*<<< orphan*/  xfs_dir2_leaf_t ;
struct xfs_dir2_leaf_entry {int /*<<< orphan*/  address; } ;
typedef  struct xfs_dir2_leaf_entry xfs_dir2_leaf_entry_t ;
struct TYPE_14__ {int /*<<< orphan*/  inumber; } ;
typedef  TYPE_3__ xfs_dir2_data_entry_t ;
struct TYPE_15__ {scalar_t__ inumber; int /*<<< orphan*/ * trans; int /*<<< orphan*/  filetype; int /*<<< orphan*/  geo; TYPE_2__* dp; } ;
typedef  TYPE_4__ xfs_da_args_t ;
struct xfs_buf {int /*<<< orphan*/ * b_addr; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* data_put_ftype ) (TYPE_3__*,int /*<<< orphan*/ ) ;struct xfs_dir2_leaf_entry* (* leaf_ents_p ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (scalar_t__) ; 
 struct xfs_dir2_leaf_entry* stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xfs_dir2_leaf_replace (TYPE_4__*) ; 
 int /*<<< orphan*/  xfs_dir2_data_log_entry (TYPE_4__*,struct xfs_buf*,TYPE_3__*) ; 
 int xfs_dir2_dataptr_to_off (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xfs_dir2_leaf_lookup_int (TYPE_4__*,struct xfs_buf**,int*,struct xfs_buf**) ; 
 int /*<<< orphan*/  xfs_dir3_leaf_check (TYPE_2__*,struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_trans_brelse (int /*<<< orphan*/ *,struct xfs_buf*) ; 

int						/* error */
xfs_dir2_leaf_replace(
	xfs_da_args_t		*args)		/* operation arguments */
{
	struct xfs_buf		*dbp;		/* data block buffer */
	xfs_dir2_data_entry_t	*dep;		/* data block entry */
	xfs_inode_t		*dp;		/* incore directory inode */
	int			error;		/* error return code */
	int			index;		/* index of leaf entry */
	struct xfs_buf		*lbp;		/* leaf buffer */
	xfs_dir2_leaf_t		*leaf;		/* leaf structure */
	xfs_dir2_leaf_entry_t	*lep;		/* leaf entry */
	xfs_trans_t		*tp;		/* transaction pointer */
	struct xfs_dir2_leaf_entry *ents;

	trace_xfs_dir2_leaf_replace(args);

	/*
	 * Look up the entry.
	 */
	if ((error = xfs_dir2_leaf_lookup_int(args, &lbp, &index, &dbp))) {
		return error;
	}
	dp = args->dp;
	leaf = lbp->b_addr;
	ents = dp->d_ops->leaf_ents_p(leaf);
	/*
	 * Point to the leaf entry, get data address from it.
	 */
	lep = &ents[index];
	/*
	 * Point to the data entry.
	 */
	dep = (xfs_dir2_data_entry_t *)
	      ((char *)dbp->b_addr +
	       xfs_dir2_dataptr_to_off(args->geo, be32_to_cpu(lep->address)));
	ASSERT(args->inumber != be64_to_cpu(dep->inumber));
	/*
	 * Put the new inode number in, log it.
	 */
	dep->inumber = cpu_to_be64(args->inumber);
	dp->d_ops->data_put_ftype(dep, args->filetype);
	tp = args->trans;
	xfs_dir2_data_log_entry(args, dbp, dep);
	xfs_dir3_leaf_check(dp, lbp);
	xfs_trans_brelse(tp, lbp);
	return 0;
}