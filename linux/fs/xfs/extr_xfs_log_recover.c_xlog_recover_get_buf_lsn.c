#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xfs_lsn_t ;
typedef  int /*<<< orphan*/  uuid_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_9__ {int /*<<< orphan*/  sb_uuid; int /*<<< orphan*/  sb_meta_uuid; } ;
struct xfs_mount {TYPE_4__ m_sb; } ;
struct xfs_dsymlink_hdr {int /*<<< orphan*/  sl_uuid; int /*<<< orphan*/  sl_lsn; } ;
struct xfs_dsb {int /*<<< orphan*/  sb_uuid; int /*<<< orphan*/  sb_meta_uuid; int /*<<< orphan*/  sb_lsn; } ;
struct xfs_dir3_blk_hdr {int /*<<< orphan*/  uuid; int /*<<< orphan*/  lsn; } ;
struct xfs_da_blkinfo {int /*<<< orphan*/  magic; } ;
struct xfs_da3_blkinfo {int /*<<< orphan*/  uuid; int /*<<< orphan*/  lsn; } ;
struct xfs_buf {void* b_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  bb_uuid; int /*<<< orphan*/  bb_lsn; } ;
struct TYPE_6__ {int /*<<< orphan*/  bb_uuid; int /*<<< orphan*/  bb_lsn; } ;
struct TYPE_8__ {TYPE_2__ l; TYPE_1__ s; } ;
struct xfs_btree_block {TYPE_3__ bb_u; } ;
struct xfs_agi {int /*<<< orphan*/  agi_uuid; int /*<<< orphan*/  agi_lsn; } ;
struct xfs_agfl {int /*<<< orphan*/  agfl_uuid; int /*<<< orphan*/  agfl_lsn; } ;
struct xfs_agf {int /*<<< orphan*/  agf_uuid; int /*<<< orphan*/  agf_lsn; } ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
#define  XFS_ABTB_CRC_MAGIC 151 
#define  XFS_ABTB_MAGIC 150 
#define  XFS_ABTC_CRC_MAGIC 149 
#define  XFS_ABTC_MAGIC 148 
#define  XFS_AGFL_MAGIC 147 
#define  XFS_AGF_MAGIC 146 
#define  XFS_AGI_MAGIC 145 
#define  XFS_ATTR3_RMT_MAGIC 144 
#define  XFS_BMAP_CRC_MAGIC 143 
#define  XFS_BMAP_MAGIC 142 
#define  XFS_DA3_NODE_MAGIC 141 
#define  XFS_DINODE_MAGIC 140 
#define  XFS_DIR3_BLOCK_MAGIC 139 
#define  XFS_DIR3_DATA_MAGIC 138 
#define  XFS_DIR3_FREE_MAGIC 137 
#define  XFS_DIR3_LEAF1_MAGIC 136 
#define  XFS_DIR3_LEAFN_MAGIC 135 
#define  XFS_DQUOT_MAGIC 134 
#define  XFS_IBT_CRC_MAGIC 133 
#define  XFS_IBT_MAGIC 132 
#define  XFS_REFC_CRC_MAGIC 131 
#define  XFS_RMAP_CRC_MAGIC 130 
#define  XFS_SB_MAGIC 129 
#define  XFS_SYMLINK_MAGIC 128 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uuid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_sb_version_hascrc (TYPE_4__*) ; 
 int /*<<< orphan*/  xfs_sb_version_hasmetauuid (TYPE_4__*) ; 

__attribute__((used)) static xfs_lsn_t
xlog_recover_get_buf_lsn(
	struct xfs_mount	*mp,
	struct xfs_buf		*bp)
{
	uint32_t		magic32;
	uint16_t		magic16;
	uint16_t		magicda;
	void			*blk = bp->b_addr;
	uuid_t			*uuid;
	xfs_lsn_t		lsn = -1;

	/* v4 filesystems always recover immediately */
	if (!xfs_sb_version_hascrc(&mp->m_sb))
		goto recover_immediately;

	magic32 = be32_to_cpu(*(__be32 *)blk);
	switch (magic32) {
	case XFS_ABTB_CRC_MAGIC:
	case XFS_ABTC_CRC_MAGIC:
	case XFS_ABTB_MAGIC:
	case XFS_ABTC_MAGIC:
	case XFS_RMAP_CRC_MAGIC:
	case XFS_REFC_CRC_MAGIC:
	case XFS_IBT_CRC_MAGIC:
	case XFS_IBT_MAGIC: {
		struct xfs_btree_block *btb = blk;

		lsn = be64_to_cpu(btb->bb_u.s.bb_lsn);
		uuid = &btb->bb_u.s.bb_uuid;
		break;
	}
	case XFS_BMAP_CRC_MAGIC:
	case XFS_BMAP_MAGIC: {
		struct xfs_btree_block *btb = blk;

		lsn = be64_to_cpu(btb->bb_u.l.bb_lsn);
		uuid = &btb->bb_u.l.bb_uuid;
		break;
	}
	case XFS_AGF_MAGIC:
		lsn = be64_to_cpu(((struct xfs_agf *)blk)->agf_lsn);
		uuid = &((struct xfs_agf *)blk)->agf_uuid;
		break;
	case XFS_AGFL_MAGIC:
		lsn = be64_to_cpu(((struct xfs_agfl *)blk)->agfl_lsn);
		uuid = &((struct xfs_agfl *)blk)->agfl_uuid;
		break;
	case XFS_AGI_MAGIC:
		lsn = be64_to_cpu(((struct xfs_agi *)blk)->agi_lsn);
		uuid = &((struct xfs_agi *)blk)->agi_uuid;
		break;
	case XFS_SYMLINK_MAGIC:
		lsn = be64_to_cpu(((struct xfs_dsymlink_hdr *)blk)->sl_lsn);
		uuid = &((struct xfs_dsymlink_hdr *)blk)->sl_uuid;
		break;
	case XFS_DIR3_BLOCK_MAGIC:
	case XFS_DIR3_DATA_MAGIC:
	case XFS_DIR3_FREE_MAGIC:
		lsn = be64_to_cpu(((struct xfs_dir3_blk_hdr *)blk)->lsn);
		uuid = &((struct xfs_dir3_blk_hdr *)blk)->uuid;
		break;
	case XFS_ATTR3_RMT_MAGIC:
		/*
		 * Remote attr blocks are written synchronously, rather than
		 * being logged. That means they do not contain a valid LSN
		 * (i.e. transactionally ordered) in them, and hence any time we
		 * see a buffer to replay over the top of a remote attribute
		 * block we should simply do so.
		 */
		goto recover_immediately;
	case XFS_SB_MAGIC:
		/*
		 * superblock uuids are magic. We may or may not have a
		 * sb_meta_uuid on disk, but it will be set in the in-core
		 * superblock. We set the uuid pointer for verification
		 * according to the superblock feature mask to ensure we check
		 * the relevant UUID in the superblock.
		 */
		lsn = be64_to_cpu(((struct xfs_dsb *)blk)->sb_lsn);
		if (xfs_sb_version_hasmetauuid(&mp->m_sb))
			uuid = &((struct xfs_dsb *)blk)->sb_meta_uuid;
		else
			uuid = &((struct xfs_dsb *)blk)->sb_uuid;
		break;
	default:
		break;
	}

	if (lsn != (xfs_lsn_t)-1) {
		if (!uuid_equal(&mp->m_sb.sb_meta_uuid, uuid))
			goto recover_immediately;
		return lsn;
	}

	magicda = be16_to_cpu(((struct xfs_da_blkinfo *)blk)->magic);
	switch (magicda) {
	case XFS_DIR3_LEAF1_MAGIC:
	case XFS_DIR3_LEAFN_MAGIC:
	case XFS_DA3_NODE_MAGIC:
		lsn = be64_to_cpu(((struct xfs_da3_blkinfo *)blk)->lsn);
		uuid = &((struct xfs_da3_blkinfo *)blk)->uuid;
		break;
	default:
		break;
	}

	if (lsn != (xfs_lsn_t)-1) {
		if (!uuid_equal(&mp->m_sb.sb_uuid, uuid))
			goto recover_immediately;
		return lsn;
	}

	/*
	 * We do individual object checks on dquot and inode buffers as they
	 * have their own individual LSN records. Also, we could have a stale
	 * buffer here, so we have to at least recognise these buffer types.
	 *
	 * A notd complexity here is inode unlinked list processing - it logs
	 * the inode directly in the buffer, but we don't know which inodes have
	 * been modified, and there is no global buffer LSN. Hence we need to
	 * recover all inode buffer types immediately. This problem will be
	 * fixed by logical logging of the unlinked list modifications.
	 */
	magic16 = be16_to_cpu(*(__be16 *)blk);
	switch (magic16) {
	case XFS_DQUOT_MAGIC:
	case XFS_DINODE_MAGIC:
		goto recover_immediately;
	default:
		break;
	}

	/* unknown buffer contents, recover immediately */

recover_immediately:
	return (xfs_lsn_t)-1;

}