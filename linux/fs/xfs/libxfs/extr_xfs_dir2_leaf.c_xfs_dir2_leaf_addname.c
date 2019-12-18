#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_dir2_leaf_entry_t ;
typedef  int xfs_dir2_db_t ;
struct xfs_dir2_data_unused {int dummy; } ;
typedef  struct xfs_dir2_data_unused xfs_dir2_data_unused_t ;
typedef  int /*<<< orphan*/  xfs_dir2_data_off_t ;
struct xfs_dir2_data_entry {int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; int /*<<< orphan*/  inumber; } ;
typedef  struct xfs_dir2_data_entry xfs_dir2_data_entry_t ;
typedef  int /*<<< orphan*/  xfs_dir2_data_aoff_t ;
struct xfs_trans {int dummy; } ;
struct xfs_inode {TYPE_1__* d_ops; } ;
struct xfs_dir3_icleaf_hdr {int count; int stale; } ;
struct xfs_dir2_leaf_tail {void* bestcount; } ;
struct xfs_dir2_leaf_entry {void* address; void* hashval; } ;
struct xfs_dir2_leaf {int dummy; } ;
typedef  struct xfs_dir2_leaf xfs_dir2_data_hdr ;
struct xfs_dir2_data_free {scalar_t__ length; scalar_t__ offset; } ;
struct xfs_da_args {int hashval; int op_flags; scalar_t__ total; TYPE_2__* geo; int /*<<< orphan*/  filetype; int /*<<< orphan*/  name; int /*<<< orphan*/  namelen; int /*<<< orphan*/  inumber; struct xfs_inode* dp; struct xfs_trans* trans; } ;
struct xfs_buf {struct xfs_dir2_leaf* b_addr; } ;
typedef  int /*<<< orphan*/  bestsp ;
typedef  scalar_t__ __be16 ;
struct TYPE_7__ {int /*<<< orphan*/  leafblk; } ;
struct TYPE_6__ {int (* data_entsize ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* leaf_hdr_to_disk ) (struct xfs_dir2_leaf*,struct xfs_dir3_icleaf_hdr*) ;scalar_t__* (* data_entry_tag_p ) (struct xfs_dir2_data_entry*) ;int /*<<< orphan*/  (* data_put_ftype ) (struct xfs_dir2_data_entry*,int /*<<< orphan*/ ) ;struct xfs_dir2_data_free* (* data_bestfree_p ) (struct xfs_dir2_leaf*) ;int /*<<< orphan*/  (* leaf_hdr_from_disk ) (struct xfs_dir3_icleaf_hdr*,struct xfs_dir2_leaf*) ;struct xfs_dir2_leaf_entry* (* leaf_ents_p ) (struct xfs_dir2_leaf*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ENOSPC ; 
 int NULLDATAOFF ; 
 int XFS_DA_OP_JUSTCHECK ; 
 int /*<<< orphan*/  XFS_DIR2_DATA_SPACE ; 
 int XFS_DIR2_NULL_DATAPTR ; 
 int be16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  be32_add_cpu (void**,int) ; 
 int be32_to_cpu (void*) ; 
 scalar_t__ cpu_to_be16 (int) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (scalar_t__*,scalar_t__*,int) ; 
 struct xfs_dir2_leaf_entry* stub1 (struct xfs_dir2_leaf*) ; 
 int /*<<< orphan*/  stub2 (struct xfs_dir3_icleaf_hdr*,struct xfs_dir2_leaf*) ; 
 int stub3 (int /*<<< orphan*/ ) ; 
 struct xfs_dir2_data_free* stub4 (struct xfs_dir2_leaf*) ; 
 struct xfs_dir2_data_free* stub5 (struct xfs_dir2_leaf*) ; 
 int /*<<< orphan*/  stub6 (struct xfs_dir2_data_entry*,int /*<<< orphan*/ ) ; 
 scalar_t__* stub7 (struct xfs_dir2_data_entry*) ; 
 int /*<<< orphan*/  stub8 (struct xfs_dir2_leaf*,struct xfs_dir3_icleaf_hdr*) ; 
 int /*<<< orphan*/  trace_xfs_dir2_leaf_addname (struct xfs_da_args*) ; 
 int /*<<< orphan*/  xfs_dir2_data_freescan (struct xfs_inode*,struct xfs_dir2_leaf*,int*) ; 
 int /*<<< orphan*/  xfs_dir2_data_log_entry (struct xfs_da_args*,struct xfs_buf*,struct xfs_dir2_data_entry*) ; 
 int /*<<< orphan*/  xfs_dir2_data_log_header (struct xfs_da_args*,struct xfs_buf*) ; 
 int xfs_dir2_data_use_free (struct xfs_da_args*,struct xfs_buf*,struct xfs_dir2_data_unused*,int /*<<< orphan*/ ,int,int*,int*) ; 
 int xfs_dir2_dataptr_to_db (TYPE_2__*,int) ; 
 int xfs_dir2_db_off_to_dataptr (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  xfs_dir2_db_to_da (TYPE_2__*,int) ; 
 int xfs_dir2_grow_inode (struct xfs_da_args*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__* xfs_dir2_leaf_bests_p (struct xfs_dir2_leaf_tail*) ; 
 int xfs_dir2_leaf_search_hash (struct xfs_da_args*,struct xfs_buf*) ; 
 struct xfs_dir2_leaf_tail* xfs_dir2_leaf_tail_p (TYPE_2__*,struct xfs_dir2_leaf*) ; 
 int xfs_dir2_leaf_to_node (struct xfs_da_args*,struct xfs_buf*) ; 
 int xfs_dir2_node_addname (struct xfs_da_args*) ; 
 int /*<<< orphan*/  xfs_dir3_data_check (struct xfs_inode*,struct xfs_buf*) ; 
 int xfs_dir3_data_init (struct xfs_da_args*,int,struct xfs_buf**) ; 
 int xfs_dir3_data_read (struct xfs_trans*,struct xfs_inode*,int /*<<< orphan*/ ,int,struct xfs_buf**) ; 
 int /*<<< orphan*/  xfs_dir3_leaf_check (struct xfs_inode*,struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_dir3_leaf_compact_x1 (struct xfs_dir3_icleaf_hdr*,struct xfs_dir2_leaf_entry*,int*,int*,int*,int*,int*) ; 
 struct xfs_dir2_leaf_entry* xfs_dir3_leaf_find_entry (struct xfs_dir3_icleaf_hdr*,struct xfs_dir2_leaf_entry*,int,int,int,int,int*,int*) ; 
 int /*<<< orphan*/  xfs_dir3_leaf_log_bests (struct xfs_da_args*,struct xfs_buf*,int,int) ; 
 int /*<<< orphan*/  xfs_dir3_leaf_log_ents (struct xfs_da_args*,struct xfs_buf*,int,int) ; 
 int /*<<< orphan*/  xfs_dir3_leaf_log_header (struct xfs_da_args*,struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_dir3_leaf_log_tail (struct xfs_da_args*,struct xfs_buf*) ; 
 int xfs_dir3_leaf_read (struct xfs_trans*,struct xfs_inode*,int /*<<< orphan*/ ,int,struct xfs_buf**) ; 
 int /*<<< orphan*/  xfs_trans_brelse (struct xfs_trans*,struct xfs_buf*) ; 

int						/* error */
xfs_dir2_leaf_addname(
	struct xfs_da_args	*args)		/* operation arguments */
{
	struct xfs_dir3_icleaf_hdr leafhdr;
	struct xfs_trans	*tp = args->trans;
	__be16			*bestsp;	/* freespace table in leaf */
	__be16			*tagp;		/* end of data entry */
	struct xfs_buf		*dbp;		/* data block buffer */
	struct xfs_buf		*lbp;		/* leaf's buffer */
	struct xfs_dir2_leaf	*leaf;		/* leaf structure */
	struct xfs_inode	*dp = args->dp;	/* incore directory inode */
	struct xfs_dir2_data_hdr *hdr;		/* data block header */
	struct xfs_dir2_data_entry *dep;	/* data block entry */
	struct xfs_dir2_leaf_entry *lep;	/* leaf entry table pointer */
	struct xfs_dir2_leaf_entry *ents;
	struct xfs_dir2_data_unused *dup;	/* data unused entry */
	struct xfs_dir2_leaf_tail *ltp;		/* leaf tail pointer */
	struct xfs_dir2_data_free *bf;		/* bestfree table */
	int			compact;	/* need to compact leaves */
	int			error;		/* error return value */
	int			grown;		/* allocated new data block */
	int			highstale = 0;	/* index of next stale leaf */
	int			i;		/* temporary, index */
	int			index;		/* leaf table position */
	int			length;		/* length of new entry */
	int			lfloglow;	/* low leaf logging index */
	int			lfloghigh;	/* high leaf logging index */
	int			lowstale = 0;	/* index of prev stale leaf */
	int			needbytes;	/* leaf block bytes needed */
	int			needlog;	/* need to log data header */
	int			needscan;	/* need to rescan data free */
	xfs_dir2_db_t		use_block;	/* data block number */

	trace_xfs_dir2_leaf_addname(args);

	error = xfs_dir3_leaf_read(tp, dp, args->geo->leafblk, -1, &lbp);
	if (error)
		return error;

	/*
	 * Look up the entry by hash value and name.
	 * We know it's not there, our caller has already done a lookup.
	 * So the index is of the entry to insert in front of.
	 * But if there are dup hash values the index is of the first of those.
	 */
	index = xfs_dir2_leaf_search_hash(args, lbp);
	leaf = lbp->b_addr;
	ltp = xfs_dir2_leaf_tail_p(args->geo, leaf);
	ents = dp->d_ops->leaf_ents_p(leaf);
	dp->d_ops->leaf_hdr_from_disk(&leafhdr, leaf);
	bestsp = xfs_dir2_leaf_bests_p(ltp);
	length = dp->d_ops->data_entsize(args->namelen);

	/*
	 * See if there are any entries with the same hash value
	 * and space in their block for the new entry.
	 * This is good because it puts multiple same-hash value entries
	 * in a data block, improving the lookup of those entries.
	 */
	for (use_block = -1, lep = &ents[index];
	     index < leafhdr.count && be32_to_cpu(lep->hashval) == args->hashval;
	     index++, lep++) {
		if (be32_to_cpu(lep->address) == XFS_DIR2_NULL_DATAPTR)
			continue;
		i = xfs_dir2_dataptr_to_db(args->geo, be32_to_cpu(lep->address));
		ASSERT(i < be32_to_cpu(ltp->bestcount));
		ASSERT(bestsp[i] != cpu_to_be16(NULLDATAOFF));
		if (be16_to_cpu(bestsp[i]) >= length) {
			use_block = i;
			break;
		}
	}
	/*
	 * Didn't find a block yet, linear search all the data blocks.
	 */
	if (use_block == -1) {
		for (i = 0; i < be32_to_cpu(ltp->bestcount); i++) {
			/*
			 * Remember a block we see that's missing.
			 */
			if (bestsp[i] == cpu_to_be16(NULLDATAOFF) &&
			    use_block == -1)
				use_block = i;
			else if (be16_to_cpu(bestsp[i]) >= length) {
				use_block = i;
				break;
			}
		}
	}
	/*
	 * How many bytes do we need in the leaf block?
	 */
	needbytes = 0;
	if (!leafhdr.stale)
		needbytes += sizeof(xfs_dir2_leaf_entry_t);
	if (use_block == -1)
		needbytes += sizeof(xfs_dir2_data_off_t);

	/*
	 * Now kill use_block if it refers to a missing block, so we
	 * can use it as an indication of allocation needed.
	 */
	if (use_block != -1 && bestsp[use_block] == cpu_to_be16(NULLDATAOFF))
		use_block = -1;
	/*
	 * If we don't have enough free bytes but we can make enough
	 * by compacting out stale entries, we'll do that.
	 */
	if ((char *)bestsp - (char *)&ents[leafhdr.count] < needbytes &&
	    leafhdr.stale > 1)
		compact = 1;

	/*
	 * Otherwise if we don't have enough free bytes we need to
	 * convert to node form.
	 */
	else if ((char *)bestsp - (char *)&ents[leafhdr.count] < needbytes) {
		/*
		 * Just checking or no space reservation, give up.
		 */
		if ((args->op_flags & XFS_DA_OP_JUSTCHECK) ||
							args->total == 0) {
			xfs_trans_brelse(tp, lbp);
			return -ENOSPC;
		}
		/*
		 * Convert to node form.
		 */
		error = xfs_dir2_leaf_to_node(args, lbp);
		if (error)
			return error;
		/*
		 * Then add the new entry.
		 */
		return xfs_dir2_node_addname(args);
	}
	/*
	 * Otherwise it will fit without compaction.
	 */
	else
		compact = 0;
	/*
	 * If just checking, then it will fit unless we needed to allocate
	 * a new data block.
	 */
	if (args->op_flags & XFS_DA_OP_JUSTCHECK) {
		xfs_trans_brelse(tp, lbp);
		return use_block == -1 ? -ENOSPC : 0;
	}
	/*
	 * If no allocations are allowed, return now before we've
	 * changed anything.
	 */
	if (args->total == 0 && use_block == -1) {
		xfs_trans_brelse(tp, lbp);
		return -ENOSPC;
	}
	/*
	 * Need to compact the leaf entries, removing stale ones.
	 * Leave one stale entry behind - the one closest to our
	 * insertion index - and we'll shift that one to our insertion
	 * point later.
	 */
	if (compact) {
		xfs_dir3_leaf_compact_x1(&leafhdr, ents, &index, &lowstale,
			&highstale, &lfloglow, &lfloghigh);
	}
	/*
	 * There are stale entries, so we'll need log-low and log-high
	 * impossibly bad values later.
	 */
	else if (leafhdr.stale) {
		lfloglow = leafhdr.count;
		lfloghigh = -1;
	}
	/*
	 * If there was no data block space found, we need to allocate
	 * a new one.
	 */
	if (use_block == -1) {
		/*
		 * Add the new data block.
		 */
		if ((error = xfs_dir2_grow_inode(args, XFS_DIR2_DATA_SPACE,
				&use_block))) {
			xfs_trans_brelse(tp, lbp);
			return error;
		}
		/*
		 * Initialize the block.
		 */
		if ((error = xfs_dir3_data_init(args, use_block, &dbp))) {
			xfs_trans_brelse(tp, lbp);
			return error;
		}
		/*
		 * If we're adding a new data block on the end we need to
		 * extend the bests table.  Copy it up one entry.
		 */
		if (use_block >= be32_to_cpu(ltp->bestcount)) {
			bestsp--;
			memmove(&bestsp[0], &bestsp[1],
				be32_to_cpu(ltp->bestcount) * sizeof(bestsp[0]));
			be32_add_cpu(&ltp->bestcount, 1);
			xfs_dir3_leaf_log_tail(args, lbp);
			xfs_dir3_leaf_log_bests(args, lbp, 0,
						be32_to_cpu(ltp->bestcount) - 1);
		}
		/*
		 * If we're filling in a previously empty block just log it.
		 */
		else
			xfs_dir3_leaf_log_bests(args, lbp, use_block, use_block);
		hdr = dbp->b_addr;
		bf = dp->d_ops->data_bestfree_p(hdr);
		bestsp[use_block] = bf[0].length;
		grown = 1;
	} else {
		/*
		 * Already had space in some data block.
		 * Just read that one in.
		 */
		error = xfs_dir3_data_read(tp, dp,
				   xfs_dir2_db_to_da(args->geo, use_block),
				   -1, &dbp);
		if (error) {
			xfs_trans_brelse(tp, lbp);
			return error;
		}
		hdr = dbp->b_addr;
		bf = dp->d_ops->data_bestfree_p(hdr);
		grown = 0;
	}
	/*
	 * Point to the biggest freespace in our data block.
	 */
	dup = (xfs_dir2_data_unused_t *)
	      ((char *)hdr + be16_to_cpu(bf[0].offset));
	needscan = needlog = 0;
	/*
	 * Mark the initial part of our freespace in use for the new entry.
	 */
	error = xfs_dir2_data_use_free(args, dbp, dup,
			(xfs_dir2_data_aoff_t)((char *)dup - (char *)hdr),
			length, &needlog, &needscan);
	if (error) {
		xfs_trans_brelse(tp, lbp);
		return error;
	}
	/*
	 * Initialize our new entry (at last).
	 */
	dep = (xfs_dir2_data_entry_t *)dup;
	dep->inumber = cpu_to_be64(args->inumber);
	dep->namelen = args->namelen;
	memcpy(dep->name, args->name, dep->namelen);
	dp->d_ops->data_put_ftype(dep, args->filetype);
	tagp = dp->d_ops->data_entry_tag_p(dep);
	*tagp = cpu_to_be16((char *)dep - (char *)hdr);
	/*
	 * Need to scan fix up the bestfree table.
	 */
	if (needscan)
		xfs_dir2_data_freescan(dp, hdr, &needlog);
	/*
	 * Need to log the data block's header.
	 */
	if (needlog)
		xfs_dir2_data_log_header(args, dbp);
	xfs_dir2_data_log_entry(args, dbp, dep);
	/*
	 * If the bests table needs to be changed, do it.
	 * Log the change unless we've already done that.
	 */
	if (be16_to_cpu(bestsp[use_block]) != be16_to_cpu(bf[0].length)) {
		bestsp[use_block] = bf[0].length;
		if (!grown)
			xfs_dir3_leaf_log_bests(args, lbp, use_block, use_block);
	}

	lep = xfs_dir3_leaf_find_entry(&leafhdr, ents, index, compact, lowstale,
				       highstale, &lfloglow, &lfloghigh);

	/*
	 * Fill in the new leaf entry.
	 */
	lep->hashval = cpu_to_be32(args->hashval);
	lep->address = cpu_to_be32(
				xfs_dir2_db_off_to_dataptr(args->geo, use_block,
				be16_to_cpu(*tagp)));
	/*
	 * Log the leaf fields and give up the buffers.
	 */
	dp->d_ops->leaf_hdr_to_disk(leaf, &leafhdr);
	xfs_dir3_leaf_log_header(args, lbp);
	xfs_dir3_leaf_log_ents(args, lbp, lfloglow, lfloghigh);
	xfs_dir3_leaf_check(dp, lbp);
	xfs_dir3_data_check(dp, dbp);
	return 0;
}