#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ if_data; } ;
struct TYPE_18__ {TYPE_1__ if_u1; } ;
struct TYPE_21__ {TYPE_3__* d_ops; TYPE_2__ i_df; } ;
typedef  TYPE_5__ xfs_inode_t ;
struct TYPE_22__ {int count; } ;
typedef  TYPE_6__ xfs_dir2_sf_hdr_t ;
struct TYPE_23__ {int /*<<< orphan*/  namelen; } ;
typedef  TYPE_7__ xfs_dir2_sf_entry_t ;
typedef  int /*<<< orphan*/  xfs_dir2_leaf_entry_t ;
typedef  int xfs_dir2_data_aoff_t ;
typedef  int /*<<< orphan*/  xfs_dir2_block_tail_t ;
struct TYPE_24__ {TYPE_4__* geo; int /*<<< orphan*/  namelen; TYPE_5__* dp; } ;
typedef  TYPE_8__ xfs_da_args_t ;
typedef  int uint ;
struct TYPE_20__ {int blksize; } ;
struct TYPE_19__ {int (* data_entsize ) (int /*<<< orphan*/ ) ;int data_first_offset; TYPE_7__* (* sf_nextentry ) (TYPE_6__*,TYPE_7__*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ) ; 
 TYPE_7__* stub3 (TYPE_6__*,TYPE_7__*) ; 
 TYPE_7__* xfs_dir2_sf_firstentry (TYPE_6__*) ; 
 int xfs_dir2_sf_get_offset (TYPE_7__*) ; 

__attribute__((used)) static int					/* pick result */
xfs_dir2_sf_addname_pick(
	xfs_da_args_t		*args,		/* operation arguments */
	int			objchange,	/* inode # size changes */
	xfs_dir2_sf_entry_t	**sfepp,	/* out(1): new entry ptr */
	xfs_dir2_data_aoff_t	*offsetp)	/* out(1): new offset */
{
	xfs_inode_t		*dp;		/* incore directory inode */
	int			holefit;	/* found hole it will fit in */
	int			i;		/* entry number */
	xfs_dir2_data_aoff_t	offset;		/* data block offset */
	xfs_dir2_sf_entry_t	*sfep;		/* shortform entry */
	xfs_dir2_sf_hdr_t	*sfp;		/* shortform structure */
	int			size;		/* entry's data size */
	int			used;		/* data bytes used */

	dp = args->dp;

	sfp = (xfs_dir2_sf_hdr_t *)dp->i_df.if_u1.if_data;
	size = dp->d_ops->data_entsize(args->namelen);
	offset = dp->d_ops->data_first_offset;
	sfep = xfs_dir2_sf_firstentry(sfp);
	holefit = 0;
	/*
	 * Loop over sf entries.
	 * Keep track of data offset and whether we've seen a place
	 * to insert the new entry.
	 */
	for (i = 0; i < sfp->count; i++) {
		if (!holefit)
			holefit = offset + size <= xfs_dir2_sf_get_offset(sfep);
		offset = xfs_dir2_sf_get_offset(sfep) +
			 dp->d_ops->data_entsize(sfep->namelen);
		sfep = dp->d_ops->sf_nextentry(sfp, sfep);
	}
	/*
	 * Calculate data bytes used excluding the new entry, if this
	 * was a data block (block form directory).
	 */
	used = offset +
	       (sfp->count + 3) * (uint)sizeof(xfs_dir2_leaf_entry_t) +
	       (uint)sizeof(xfs_dir2_block_tail_t);
	/*
	 * If it won't fit in a block form then we can't insert it,
	 * we'll go back, convert to block, then try the insert and convert
	 * to leaf.
	 */
	if (used + (holefit ? 0 : size) > args->geo->blksize)
		return 0;
	/*
	 * If changing the inode number size, do it the hard way.
	 */
	if (objchange)
		return 2;
	/*
	 * If it won't fit at the end then do it the hard way (use the hole).
	 */
	if (used + size > args->geo->blksize)
		return 2;
	/*
	 * Do it the easy way.
	 */
	*sfepp = sfep;
	*offsetp = offset;
	return 1;
}