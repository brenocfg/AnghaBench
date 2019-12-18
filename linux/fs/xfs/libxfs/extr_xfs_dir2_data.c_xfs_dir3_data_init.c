#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
struct TYPE_20__ {int /*<<< orphan*/  sb_meta_uuid; } ;
struct TYPE_16__ {TYPE_6__ m_sb; } ;
typedef  TYPE_2__ xfs_mount_t ;
struct TYPE_17__ {TYPE_1__* d_ops; int /*<<< orphan*/  i_ino; TYPE_2__* i_mount; } ;
typedef  TYPE_3__ xfs_inode_t ;
typedef  int /*<<< orphan*/  xfs_dir2_db_t ;
struct TYPE_18__ {void* length; void* freetag; } ;
typedef  TYPE_4__ xfs_dir2_data_unused_t ;
struct xfs_dir3_blk_hdr {void* magic; int /*<<< orphan*/  uuid; void* owner; void* blkno; } ;
typedef  struct xfs_dir3_blk_hdr xfs_dir2_data_hdr_t ;
struct TYPE_19__ {TYPE_8__* geo; int /*<<< orphan*/ * trans; TYPE_3__* dp; } ;
typedef  TYPE_5__ xfs_da_args_t ;
typedef  int uint ;
struct xfs_dir2_data_free {void* length; void* offset; } ;
struct xfs_buf {int /*<<< orphan*/  b_bn; struct xfs_dir3_blk_hdr* b_addr; int /*<<< orphan*/ * b_ops; } ;
struct TYPE_21__ {int blksize; } ;
struct TYPE_15__ {int data_entry_offset; TYPE_4__* (* data_unused_p ) (struct xfs_dir3_blk_hdr*) ;struct xfs_dir2_data_free* (* data_bestfree_p ) (struct xfs_dir3_blk_hdr*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_BLFT_DIR_DATA_BUF ; 
 int /*<<< orphan*/  XFS_DATA_FORK ; 
 int XFS_DIR2_DATA_FD_COUNT ; 
 int XFS_DIR2_DATA_FREE_TAG ; 
 int /*<<< orphan*/  XFS_DIR2_DATA_MAGIC ; 
 int /*<<< orphan*/  XFS_DIR3_DATA_MAGIC ; 
 void* cpu_to_be16 (int) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct xfs_dir3_blk_hdr*,int /*<<< orphan*/ ,int) ; 
 struct xfs_dir2_data_free* stub1 (struct xfs_dir3_blk_hdr*) ; 
 TYPE_4__* stub2 (struct xfs_dir3_blk_hdr*) ; 
 int /*<<< orphan*/  uuid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int xfs_da_get_buf (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int,struct xfs_buf**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dir2_data_log_header (TYPE_5__*,struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_dir2_data_log_unused (TYPE_5__*,struct xfs_buf*,TYPE_4__*) ; 
 void** xfs_dir2_data_unused_tag_p (TYPE_4__*) ; 
 int /*<<< orphan*/  xfs_dir2_db_to_da (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dir3_data_buf_ops ; 
 scalar_t__ xfs_sb_version_hascrc (TYPE_6__*) ; 
 int /*<<< orphan*/  xfs_trans_buf_set_type (int /*<<< orphan*/ *,struct xfs_buf*,int /*<<< orphan*/ ) ; 

int						/* error */
xfs_dir3_data_init(
	xfs_da_args_t		*args,		/* directory operation args */
	xfs_dir2_db_t		blkno,		/* logical dir block number */
	struct xfs_buf		**bpp)		/* output block buffer */
{
	struct xfs_buf		*bp;		/* block buffer */
	xfs_dir2_data_hdr_t	*hdr;		/* data block header */
	xfs_inode_t		*dp;		/* incore directory inode */
	xfs_dir2_data_unused_t	*dup;		/* unused entry pointer */
	struct xfs_dir2_data_free *bf;
	int			error;		/* error return value */
	int			i;		/* bestfree index */
	xfs_mount_t		*mp;		/* filesystem mount point */
	xfs_trans_t		*tp;		/* transaction pointer */
	int                     t;              /* temp */

	dp = args->dp;
	mp = dp->i_mount;
	tp = args->trans;
	/*
	 * Get the buffer set up for the block.
	 */
	error = xfs_da_get_buf(tp, dp, xfs_dir2_db_to_da(args->geo, blkno),
			       -1, &bp, XFS_DATA_FORK);
	if (error)
		return error;
	bp->b_ops = &xfs_dir3_data_buf_ops;
	xfs_trans_buf_set_type(tp, bp, XFS_BLFT_DIR_DATA_BUF);

	/*
	 * Initialize the header.
	 */
	hdr = bp->b_addr;
	if (xfs_sb_version_hascrc(&mp->m_sb)) {
		struct xfs_dir3_blk_hdr *hdr3 = bp->b_addr;

		memset(hdr3, 0, sizeof(*hdr3));
		hdr3->magic = cpu_to_be32(XFS_DIR3_DATA_MAGIC);
		hdr3->blkno = cpu_to_be64(bp->b_bn);
		hdr3->owner = cpu_to_be64(dp->i_ino);
		uuid_copy(&hdr3->uuid, &mp->m_sb.sb_meta_uuid);

	} else
		hdr->magic = cpu_to_be32(XFS_DIR2_DATA_MAGIC);

	bf = dp->d_ops->data_bestfree_p(hdr);
	bf[0].offset = cpu_to_be16(dp->d_ops->data_entry_offset);
	for (i = 1; i < XFS_DIR2_DATA_FD_COUNT; i++) {
		bf[i].length = 0;
		bf[i].offset = 0;
	}

	/*
	 * Set up an unused entry for the block's body.
	 */
	dup = dp->d_ops->data_unused_p(hdr);
	dup->freetag = cpu_to_be16(XFS_DIR2_DATA_FREE_TAG);

	t = args->geo->blksize - (uint)dp->d_ops->data_entry_offset;
	bf[0].length = cpu_to_be16(t);
	dup->length = cpu_to_be16(t);
	*xfs_dir2_data_unused_tag_p(dup) = cpu_to_be16((char *)dup - (char *)hdr);
	/*
	 * Log it and return it.
	 */
	xfs_dir2_data_log_header(args, bp);
	xfs_dir2_data_log_unused(args, bp, dup);
	*bpp = bp;
	return 0;
}