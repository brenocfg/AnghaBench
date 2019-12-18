#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_11__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ xfs_ino_t ;
struct TYPE_28__ {scalar_t__ magic; } ;
typedef  TYPE_5__ xfs_dir2_leaf_t ;
struct xfs_dir2_leaf_entry {int /*<<< orphan*/  address; } ;
typedef  struct xfs_dir2_leaf_entry xfs_dir2_leaf_entry_t ;
typedef  TYPE_5__ xfs_dir2_data_hdr_t ;
struct TYPE_29__ {int /*<<< orphan*/  inumber; } ;
typedef  TYPE_7__ xfs_dir2_data_entry_t ;
struct TYPE_27__ {int active; TYPE_9__* blk; } ;
struct TYPE_26__ {TYPE_11__* bp; } ;
struct TYPE_30__ {int extravalid; TYPE_4__ path; TYPE_3__ extrablk; int /*<<< orphan*/  mp; TYPE_10__* args; } ;
typedef  TYPE_8__ xfs_da_state_t ;
struct TYPE_31__ {scalar_t__ magic; size_t index; TYPE_11__* bp; } ;
typedef  TYPE_9__ xfs_da_state_blk_t ;
struct TYPE_22__ {scalar_t__ inumber; int filetype; int /*<<< orphan*/  trans; TYPE_2__* dp; int /*<<< orphan*/  geo; } ;
typedef  TYPE_10__ xfs_da_args_t ;
struct TYPE_25__ {TYPE_1__* d_ops; int /*<<< orphan*/  i_mount; } ;
struct TYPE_24__ {int /*<<< orphan*/  (* data_put_ftype ) (TYPE_7__*,int) ;struct xfs_dir2_leaf_entry* (* leaf_ents_p ) (TYPE_5__*) ;} ;
struct TYPE_23__ {TYPE_5__* b_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int EEXIST ; 
 int /*<<< orphan*/  XFS_DIR2_DATA_MAGIC ; 
 scalar_t__ XFS_DIR2_LEAFN_MAGIC ; 
 int /*<<< orphan*/  XFS_DIR3_DATA_MAGIC ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (scalar_t__) ; 
 struct xfs_dir2_leaf_entry* stub1 (TYPE_5__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_7__*,int) ; 
 int /*<<< orphan*/  trace_xfs_dir2_node_replace (TYPE_10__*) ; 
 int xfs_da3_node_lookup_int (TYPE_8__*,int*) ; 
 TYPE_8__* xfs_da_state_alloc () ; 
 int /*<<< orphan*/  xfs_da_state_free (TYPE_8__*) ; 
 int /*<<< orphan*/  xfs_dir2_data_log_entry (TYPE_10__*,TYPE_11__*,TYPE_7__*) ; 
 int xfs_dir2_dataptr_to_off (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_brelse (int /*<<< orphan*/ ,TYPE_11__*) ; 

int						/* error */
xfs_dir2_node_replace(
	xfs_da_args_t		*args)		/* operation arguments */
{
	xfs_da_state_blk_t	*blk;		/* leaf block */
	xfs_dir2_data_hdr_t	*hdr;		/* data block header */
	xfs_dir2_data_entry_t	*dep;		/* data entry changed */
	int			error;		/* error return value */
	int			i;		/* btree level */
	xfs_ino_t		inum;		/* new inode number */
	int			ftype;		/* new file type */
	xfs_dir2_leaf_t		*leaf;		/* leaf structure */
	xfs_dir2_leaf_entry_t	*lep;		/* leaf entry being changed */
	int			rval;		/* internal return value */
	xfs_da_state_t		*state;		/* btree cursor */

	trace_xfs_dir2_node_replace(args);

	/*
	 * Allocate and initialize the btree cursor.
	 */
	state = xfs_da_state_alloc();
	state->args = args;
	state->mp = args->dp->i_mount;

	/*
	 * We have to save new inode number and ftype since
	 * xfs_da3_node_lookup_int() is going to overwrite them
	 */
	inum = args->inumber;
	ftype = args->filetype;

	/*
	 * Lookup the entry to change in the btree.
	 */
	error = xfs_da3_node_lookup_int(state, &rval);
	if (error) {
		rval = error;
	}
	/*
	 * It should be found, since the vnodeops layer has looked it up
	 * and locked it.  But paranoia is good.
	 */
	if (rval == -EEXIST) {
		struct xfs_dir2_leaf_entry *ents;
		/*
		 * Find the leaf entry.
		 */
		blk = &state->path.blk[state->path.active - 1];
		ASSERT(blk->magic == XFS_DIR2_LEAFN_MAGIC);
		leaf = blk->bp->b_addr;
		ents = args->dp->d_ops->leaf_ents_p(leaf);
		lep = &ents[blk->index];
		ASSERT(state->extravalid);
		/*
		 * Point to the data entry.
		 */
		hdr = state->extrablk.bp->b_addr;
		ASSERT(hdr->magic == cpu_to_be32(XFS_DIR2_DATA_MAGIC) ||
		       hdr->magic == cpu_to_be32(XFS_DIR3_DATA_MAGIC));
		dep = (xfs_dir2_data_entry_t *)
		      ((char *)hdr +
		       xfs_dir2_dataptr_to_off(args->geo,
					       be32_to_cpu(lep->address)));
		ASSERT(inum != be64_to_cpu(dep->inumber));
		/*
		 * Fill in the new inode number and log the entry.
		 */
		dep->inumber = cpu_to_be64(inum);
		args->dp->d_ops->data_put_ftype(dep, ftype);
		xfs_dir2_data_log_entry(args, state->extrablk.bp, dep);
		rval = 0;
	}
	/*
	 * Didn't find it, and we're holding a data block.  Drop it.
	 */
	else if (state->extravalid) {
		xfs_trans_brelse(args->trans, state->extrablk.bp);
		state->extrablk.bp = NULL;
	}
	/*
	 * Release all the buffers in the cursor.
	 */
	for (i = 0; i < state->path.active; i++) {
		xfs_trans_brelse(args->trans, state->path.blk[i].bp);
		state->path.blk[i].bp = NULL;
	}
	xfs_da_state_free(state);
	return rval;
}