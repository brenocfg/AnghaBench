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
typedef  int xfs_dir2_db_t ;
struct xfs_dir2_data_unused {int dummy; } ;
typedef  struct xfs_dir2_data_unused xfs_dir2_data_unused_t ;
struct xfs_dir2_data_entry {int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; int /*<<< orphan*/  inumber; } ;
typedef  struct xfs_dir2_data_entry xfs_dir2_data_entry_t ;
typedef  scalar_t__ xfs_dir2_data_aoff_t ;
typedef  scalar_t__ xfs_dablk_t ;
struct xfs_trans {int dummy; } ;
struct xfs_inode {TYPE_1__* d_ops; } ;
struct xfs_dir2_free {int dummy; } ;
typedef  struct xfs_dir2_free xfs_dir2_data_hdr ;
struct xfs_dir2_data_free {int /*<<< orphan*/  length; int /*<<< orphan*/  offset; } ;
struct xfs_da_state_blk {int dummy; } ;
struct xfs_da_args {int op_flags; int index; scalar_t__ blkno; int /*<<< orphan*/  filetype; int /*<<< orphan*/  name; int /*<<< orphan*/  namelen; int /*<<< orphan*/  inumber; int /*<<< orphan*/  geo; struct xfs_inode* dp; struct xfs_trans* trans; } ;
struct xfs_buf {struct xfs_dir2_free* b_addr; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {int (* data_entsize ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/ * (* free_bests_p ) (struct xfs_dir2_free*) ;int /*<<< orphan*/ * (* data_entry_tag_p ) (struct xfs_dir2_data_entry*) ;int /*<<< orphan*/  (* data_put_ftype ) (struct xfs_dir2_data_entry*,int /*<<< orphan*/ ) ;struct xfs_dir2_data_free* (* data_bestfree_p ) (struct xfs_dir2_free*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ENOSPC ; 
 int XFS_DA_OP_JUSTCHECK ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 struct xfs_dir2_data_free* stub2 (struct xfs_dir2_free*) ; 
 int /*<<< orphan*/  stub3 (struct xfs_dir2_data_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub4 (struct xfs_dir2_data_entry*) ; 
 int /*<<< orphan*/ * stub5 (struct xfs_dir2_free*) ; 
 int /*<<< orphan*/  xfs_dir2_data_freescan (struct xfs_inode*,struct xfs_dir2_free*,int*) ; 
 int /*<<< orphan*/  xfs_dir2_data_log_entry (struct xfs_da_args*,struct xfs_buf*,struct xfs_dir2_data_entry*) ; 
 int /*<<< orphan*/  xfs_dir2_data_log_header (struct xfs_da_args*,struct xfs_buf*) ; 
 int xfs_dir2_data_use_free (struct xfs_da_args*,struct xfs_buf*,struct xfs_dir2_data_unused*,scalar_t__,int,int*,int*) ; 
 int /*<<< orphan*/  xfs_dir2_db_to_da (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xfs_dir2_free_log_bests (struct xfs_da_args*,struct xfs_buf*,int,int) ; 
 int xfs_dir2_node_add_datablk (struct xfs_da_args*,struct xfs_da_state_blk*,int*,struct xfs_buf**,struct xfs_buf**,int*) ; 
 int xfs_dir2_node_find_freeblk (struct xfs_da_args*,struct xfs_da_state_blk*,int*,struct xfs_buf**,int*,int) ; 
 int xfs_dir3_data_read (struct xfs_trans*,struct xfs_inode*,int /*<<< orphan*/ ,int,struct xfs_buf**) ; 
 int /*<<< orphan*/  xfs_trans_brelse (struct xfs_trans*,struct xfs_buf*) ; 

__attribute__((used)) static int
xfs_dir2_node_addname_int(
	struct xfs_da_args	*args,		/* operation arguments */
	struct xfs_da_state_blk	*fblk)		/* optional freespace block */
{
	struct xfs_dir2_data_unused *dup;	/* data unused entry pointer */
	struct xfs_dir2_data_entry *dep;	/* data entry pointer */
	struct xfs_dir2_data_hdr *hdr;		/* data block header */
	struct xfs_dir2_data_free *bf;
	struct xfs_dir2_free	*free = NULL;	/* freespace block structure */
	struct xfs_trans	*tp = args->trans;
	struct xfs_inode	*dp = args->dp;
	struct xfs_buf		*dbp;		/* data block buffer */
	struct xfs_buf		*fbp;		/* freespace buffer */
	xfs_dir2_data_aoff_t	aoff;
	xfs_dir2_db_t		dbno;		/* data block number */
	int			error;		/* error return value */
	int			findex;		/* freespace entry index */
	int			length;		/* length of the new entry */
	int			logfree = 0;	/* need to log free entry */
	int			needlog = 0;	/* need to log data header */
	int			needscan = 0;	/* need to rescan data frees */
	__be16			*tagp;		/* data entry tag pointer */
	__be16			*bests;

	length = dp->d_ops->data_entsize(args->namelen);
	error = xfs_dir2_node_find_freeblk(args, fblk, &dbno, &fbp, &findex,
					   length);
	if (error)
		return error;

	/*
	 * Now we know if we must allocate blocks, so if we are checking whether
	 * we can insert without allocation then we can return now.
	 */
	if (args->op_flags & XFS_DA_OP_JUSTCHECK) {
		if (dbno == -1)
			return -ENOSPC;
		return 0;
	}

	/*
	 * If we don't have a data block, we need to allocate one and make
	 * the freespace entries refer to it.
	 */
	if (dbno == -1) {
		/* we're going to have to log the free block index later */
		logfree = 1;
		error = xfs_dir2_node_add_datablk(args, fblk, &dbno, &dbp, &fbp,
						  &findex);
	} else {
		/* Read the data block in. */
		error = xfs_dir3_data_read(tp, dp,
					   xfs_dir2_db_to_da(args->geo, dbno),
					   -1, &dbp);
	}
	if (error)
		return error;

	/* setup for data block up now */
	hdr = dbp->b_addr;
	bf = dp->d_ops->data_bestfree_p(hdr);
	ASSERT(be16_to_cpu(bf[0].length) >= length);

	/* Point to the existing unused space. */
	dup = (xfs_dir2_data_unused_t *)
	      ((char *)hdr + be16_to_cpu(bf[0].offset));

	/* Mark the first part of the unused space, inuse for us. */
	aoff = (xfs_dir2_data_aoff_t)((char *)dup - (char *)hdr);
	error = xfs_dir2_data_use_free(args, dbp, dup, aoff, length,
			&needlog, &needscan);
	if (error) {
		xfs_trans_brelse(tp, dbp);
		return error;
	}

	/* Fill in the new entry and log it. */
	dep = (xfs_dir2_data_entry_t *)dup;
	dep->inumber = cpu_to_be64(args->inumber);
	dep->namelen = args->namelen;
	memcpy(dep->name, args->name, dep->namelen);
	dp->d_ops->data_put_ftype(dep, args->filetype);
	tagp = dp->d_ops->data_entry_tag_p(dep);
	*tagp = cpu_to_be16((char *)dep - (char *)hdr);
	xfs_dir2_data_log_entry(args, dbp, dep);

	/* Rescan the freespace and log the data block if needed. */
	if (needscan)
		xfs_dir2_data_freescan(dp, hdr, &needlog);
	if (needlog)
		xfs_dir2_data_log_header(args, dbp);

	/* If the freespace block entry is now wrong, update it. */
	free = fbp->b_addr;
	bests = dp->d_ops->free_bests_p(free);
	if (bests[findex] != bf[0].length) {
		bests[findex] = bf[0].length;
		logfree = 1;
	}

	/* Log the freespace entry if needed. */
	if (logfree)
		xfs_dir2_free_log_bests(args, fbp, findex, findex);

	/* Return the data block and offset in args. */
	args->blkno = (xfs_dablk_t)dbno;
	args->index = be16_to_cpu(*tagp);
	return 0;
}