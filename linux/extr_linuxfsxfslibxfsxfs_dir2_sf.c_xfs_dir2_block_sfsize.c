#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  m_sb; struct xfs_da_geometry* m_dir_geo; } ;
typedef  TYPE_2__ xfs_mount_t ;
struct TYPE_17__ {TYPE_1__* d_ops; TYPE_2__* i_mount; } ;
typedef  TYPE_3__ xfs_inode_t ;
typedef  scalar_t__ xfs_ino_t ;
struct TYPE_18__ {int count; int i8count; } ;
typedef  TYPE_4__ xfs_dir2_sf_hdr_t ;
struct TYPE_19__ {int /*<<< orphan*/  address; } ;
typedef  TYPE_5__ xfs_dir2_leaf_entry_t ;
typedef  int xfs_dir2_dataptr_t ;
typedef  int /*<<< orphan*/  xfs_dir2_data_hdr_t ;
struct TYPE_20__ {int namelen; char* name; int /*<<< orphan*/  inumber; } ;
typedef  TYPE_6__ xfs_dir2_data_entry_t ;
struct TYPE_21__ {int /*<<< orphan*/  count; } ;
typedef  TYPE_7__ xfs_dir2_block_tail_t ;
typedef  int /*<<< orphan*/  u8 ;
struct xfs_da_geometry {int dummy; } ;
struct TYPE_15__ {int /*<<< orphan*/  (* sf_put_parent_ino ) (TYPE_4__*,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ XFS_DIR2_MAX_SHORT_INUM ; 
 int XFS_DIR2_NULL_DATAPTR ; 
 int XFS_IFORK_DSIZE (TYPE_3__*) ; 
 int XFS_INO32_SIZE ; 
 int XFS_INO64_SIZE ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,scalar_t__) ; 
 TYPE_5__* xfs_dir2_block_leaf_p (TYPE_7__*) ; 
 TYPE_7__* xfs_dir2_block_tail_p (struct xfs_da_geometry*,int /*<<< orphan*/ *) ; 
 int xfs_dir2_dataptr_to_off (struct xfs_da_geometry*,int) ; 
 int xfs_dir2_sf_hdr_size (int) ; 
 scalar_t__ xfs_sb_version_hasftype (int /*<<< orphan*/ *) ; 

int						/* size for sf form */
xfs_dir2_block_sfsize(
	xfs_inode_t		*dp,		/* incore inode pointer */
	xfs_dir2_data_hdr_t	*hdr,		/* block directory data */
	xfs_dir2_sf_hdr_t	*sfhp)		/* output: header for sf form */
{
	xfs_dir2_dataptr_t	addr;		/* data entry address */
	xfs_dir2_leaf_entry_t	*blp;		/* leaf area of the block */
	xfs_dir2_block_tail_t	*btp;		/* tail area of the block */
	int			count;		/* shortform entry count */
	xfs_dir2_data_entry_t	*dep;		/* data entry in the block */
	int			i;		/* block entry index */
	int			i8count;	/* count of big-inode entries */
	int			isdot;		/* entry is "." */
	int			isdotdot;	/* entry is ".." */
	xfs_mount_t		*mp;		/* mount structure pointer */
	int			namelen;	/* total name bytes */
	xfs_ino_t		parent = 0;	/* parent inode number */
	int			size=0;		/* total computed size */
	int			has_ftype;
	struct xfs_da_geometry	*geo;

	mp = dp->i_mount;
	geo = mp->m_dir_geo;

	/*
	 * if there is a filetype field, add the extra byte to the namelen
	 * for each entry that we see.
	 */
	has_ftype = xfs_sb_version_hasftype(&mp->m_sb) ? 1 : 0;

	count = i8count = namelen = 0;
	btp = xfs_dir2_block_tail_p(geo, hdr);
	blp = xfs_dir2_block_leaf_p(btp);

	/*
	 * Iterate over the block's data entries by using the leaf pointers.
	 */
	for (i = 0; i < be32_to_cpu(btp->count); i++) {
		if ((addr = be32_to_cpu(blp[i].address)) == XFS_DIR2_NULL_DATAPTR)
			continue;
		/*
		 * Calculate the pointer to the entry at hand.
		 */
		dep = (xfs_dir2_data_entry_t *)((char *)hdr +
				xfs_dir2_dataptr_to_off(geo, addr));
		/*
		 * Detect . and .., so we can special-case them.
		 * . is not included in sf directories.
		 * .. is included by just the parent inode number.
		 */
		isdot = dep->namelen == 1 && dep->name[0] == '.';
		isdotdot =
			dep->namelen == 2 &&
			dep->name[0] == '.' && dep->name[1] == '.';

		if (!isdot)
			i8count += be64_to_cpu(dep->inumber) > XFS_DIR2_MAX_SHORT_INUM;

		/* take into account the file type field */
		if (!isdot && !isdotdot) {
			count++;
			namelen += dep->namelen + has_ftype;
		} else if (isdotdot)
			parent = be64_to_cpu(dep->inumber);
		/*
		 * Calculate the new size, see if we should give up yet.
		 */
		size = xfs_dir2_sf_hdr_size(i8count) +	/* header */
		       count * 3 * sizeof(u8) +		/* namelen + offset */
		       namelen +			/* name */
		       (i8count ?			/* inumber */
				count * XFS_INO64_SIZE :
				count * XFS_INO32_SIZE);
		if (size > XFS_IFORK_DSIZE(dp))
			return size;		/* size value is a failure */
	}
	/*
	 * Create the output header, if it worked.
	 */
	sfhp->count = count;
	sfhp->i8count = i8count;
	dp->d_ops->sf_put_parent_ino(sfhp, parent);
	return size;
}