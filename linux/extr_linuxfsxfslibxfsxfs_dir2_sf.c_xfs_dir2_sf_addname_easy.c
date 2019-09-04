#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int di_size; } ;
struct TYPE_18__ {scalar_t__ if_data; } ;
struct TYPE_19__ {TYPE_1__ if_u1; } ;
struct TYPE_22__ {TYPE_4__ i_d; TYPE_3__* d_ops; TYPE_2__ i_df; } ;
typedef  TYPE_5__ xfs_inode_t ;
struct TYPE_23__ {int /*<<< orphan*/  i8count; int /*<<< orphan*/  count; } ;
typedef  TYPE_6__ xfs_dir2_sf_hdr_t ;
struct TYPE_24__ {int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; } ;
typedef  TYPE_7__ xfs_dir2_sf_entry_t ;
typedef  int /*<<< orphan*/  xfs_dir2_data_aoff_t ;
struct TYPE_25__ {scalar_t__ inumber; int /*<<< orphan*/  filetype; int /*<<< orphan*/  name; int /*<<< orphan*/  namelen; TYPE_5__* dp; } ;
typedef  TYPE_8__ xfs_da_args_t ;
struct TYPE_20__ {int /*<<< orphan*/  (* sf_put_ftype ) (TYPE_7__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* sf_put_ino ) (TYPE_6__*,TYPE_7__*,scalar_t__) ;int /*<<< orphan*/  (* sf_entsize ) (TYPE_6__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_DATA_FORK ; 
 scalar_t__ XFS_DIR2_MAX_SHORT_INUM ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_6__*,TYPE_7__*,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dir2_sf_check (TYPE_8__*) ; 
 int /*<<< orphan*/  xfs_dir2_sf_put_offset (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_idata_realloc (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xfs_dir2_sf_addname_easy(
	xfs_da_args_t		*args,		/* operation arguments */
	xfs_dir2_sf_entry_t	*sfep,		/* pointer to new entry */
	xfs_dir2_data_aoff_t	offset,		/* offset to use for new ent */
	int			new_isize)	/* new directory size */
{
	int			byteoff;	/* byte offset in sf dir */
	xfs_inode_t		*dp;		/* incore directory inode */
	xfs_dir2_sf_hdr_t	*sfp;		/* shortform structure */

	dp = args->dp;

	sfp = (xfs_dir2_sf_hdr_t *)dp->i_df.if_u1.if_data;
	byteoff = (int)((char *)sfep - (char *)sfp);
	/*
	 * Grow the in-inode space.
	 */
	xfs_idata_realloc(dp, dp->d_ops->sf_entsize(sfp, args->namelen),
			  XFS_DATA_FORK);
	/*
	 * Need to set up again due to realloc of the inode data.
	 */
	sfp = (xfs_dir2_sf_hdr_t *)dp->i_df.if_u1.if_data;
	sfep = (xfs_dir2_sf_entry_t *)((char *)sfp + byteoff);
	/*
	 * Fill in the new entry.
	 */
	sfep->namelen = args->namelen;
	xfs_dir2_sf_put_offset(sfep, offset);
	memcpy(sfep->name, args->name, sfep->namelen);
	dp->d_ops->sf_put_ino(sfp, sfep, args->inumber);
	dp->d_ops->sf_put_ftype(sfep, args->filetype);

	/*
	 * Update the header and inode.
	 */
	sfp->count++;
	if (args->inumber > XFS_DIR2_MAX_SHORT_INUM)
		sfp->i8count++;
	dp->i_d.di_size = new_isize;
	xfs_dir2_sf_check(args);
}