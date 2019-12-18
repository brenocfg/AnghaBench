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
typedef  scalar_t__ xfs_lsn_t ;
typedef  int /*<<< orphan*/  xfs_buf_log_format_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct xfs_mount {int /*<<< orphan*/  m_sb; } ;
struct xfs_da_blkinfo {int /*<<< orphan*/  magic; } ;
struct TYPE_2__ {scalar_t__ li_lsn; } ;
struct xfs_buf_log_item {TYPE_1__ bli_item; } ;
struct xfs_buf {scalar_t__ b_iodone; struct xfs_buf_log_item* b_log_item; int /*<<< orphan*/ * b_ops; struct xfs_da_blkinfo* b_addr; } ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ NULLCOMMITLSN ; 
#define  XFS_ABTB_CRC_MAGIC 159 
#define  XFS_ABTB_MAGIC 158 
#define  XFS_ABTC_CRC_MAGIC 157 
#define  XFS_ABTC_MAGIC 156 
 int /*<<< orphan*/  XFS_AGFL_MAGIC ; 
 int /*<<< orphan*/  XFS_AGF_MAGIC ; 
 int /*<<< orphan*/  XFS_AGI_MAGIC ; 
 int /*<<< orphan*/  XFS_ATTR3_LEAF_MAGIC ; 
 int /*<<< orphan*/  XFS_ATTR3_RMT_MAGIC ; 
 int /*<<< orphan*/  XFS_ATTR_LEAF_MAGIC ; 
#define  XFS_BLFT_AGFL_BUF 155 
#define  XFS_BLFT_AGF_BUF 154 
#define  XFS_BLFT_AGI_BUF 153 
#define  XFS_BLFT_ATTR_LEAF_BUF 152 
#define  XFS_BLFT_ATTR_RMT_BUF 151 
#define  XFS_BLFT_BTREE_BUF 150 
#define  XFS_BLFT_DA_NODE_BUF 149 
#define  XFS_BLFT_DINO_BUF 148 
#define  XFS_BLFT_DIR_BLOCK_BUF 147 
#define  XFS_BLFT_DIR_DATA_BUF 146 
#define  XFS_BLFT_DIR_FREE_BUF 145 
#define  XFS_BLFT_DIR_LEAF1_BUF 144 
#define  XFS_BLFT_DIR_LEAFN_BUF 143 
#define  XFS_BLFT_GDQUOT_BUF 142 
#define  XFS_BLFT_PDQUOT_BUF 141 
#define  XFS_BLFT_RTBITMAP_BUF 140 
#define  XFS_BLFT_RTSUMMARY_BUF 139 
#define  XFS_BLFT_SB_BUF 138 
#define  XFS_BLFT_SYMLINK_BUF 137 
#define  XFS_BLFT_UDQUOT_BUF 136 
#define  XFS_BMAP_CRC_MAGIC 135 
#define  XFS_BMAP_MAGIC 134 
 int /*<<< orphan*/  XFS_DA3_NODE_MAGIC ; 
 int /*<<< orphan*/  XFS_DA_NODE_MAGIC ; 
 int /*<<< orphan*/  XFS_DINODE_MAGIC ; 
 int /*<<< orphan*/  XFS_DIR2_BLOCK_MAGIC ; 
 int /*<<< orphan*/  XFS_DIR2_DATA_MAGIC ; 
 int /*<<< orphan*/  XFS_DIR2_FREE_MAGIC ; 
 int /*<<< orphan*/  XFS_DIR2_LEAF1_MAGIC ; 
 int /*<<< orphan*/  XFS_DIR2_LEAFN_MAGIC ; 
 int /*<<< orphan*/  XFS_DIR3_BLOCK_MAGIC ; 
 int /*<<< orphan*/  XFS_DIR3_DATA_MAGIC ; 
 int /*<<< orphan*/  XFS_DIR3_FREE_MAGIC ; 
 int /*<<< orphan*/  XFS_DIR3_LEAF1_MAGIC ; 
 int /*<<< orphan*/  XFS_DIR3_LEAFN_MAGIC ; 
 int /*<<< orphan*/  XFS_DQUOT_MAGIC ; 
#define  XFS_FIBT_CRC_MAGIC 133 
#define  XFS_FIBT_MAGIC 132 
#define  XFS_IBT_CRC_MAGIC 131 
#define  XFS_IBT_MAGIC 130 
#define  XFS_REFC_CRC_MAGIC 129 
#define  XFS_RMAP_CRC_MAGIC 128 
 int /*<<< orphan*/  XFS_SB_MAGIC ; 
 int /*<<< orphan*/  XFS_SYMLINK_MAGIC ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_agf_buf_ops ; 
 int /*<<< orphan*/  xfs_agfl_buf_ops ; 
 int /*<<< orphan*/  xfs_agi_buf_ops ; 
 int /*<<< orphan*/  xfs_alert (struct xfs_mount*,char*) ; 
 int /*<<< orphan*/  xfs_attr3_leaf_buf_ops ; 
 int /*<<< orphan*/  xfs_attr3_rmt_buf_ops ; 
 int xfs_blft_from_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_bmbt_buf_ops ; 
 int /*<<< orphan*/  xfs_bnobt_buf_ops ; 
 int /*<<< orphan*/  xfs_buf_item_init (struct xfs_buf*,struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_cntbt_buf_ops ; 
 int /*<<< orphan*/  xfs_da3_node_buf_ops ; 
 int /*<<< orphan*/  xfs_dir3_block_buf_ops ; 
 int /*<<< orphan*/  xfs_dir3_data_buf_ops ; 
 int /*<<< orphan*/  xfs_dir3_free_buf_ops ; 
 int /*<<< orphan*/  xfs_dir3_leaf1_buf_ops ; 
 int /*<<< orphan*/  xfs_dir3_leafn_buf_ops ; 
 int /*<<< orphan*/  xfs_dquot_buf_ops ; 
 int /*<<< orphan*/  xfs_finobt_buf_ops ; 
 int /*<<< orphan*/  xfs_inobt_buf_ops ; 
 int /*<<< orphan*/  xfs_inode_buf_ops ; 
 int /*<<< orphan*/  xfs_refcountbt_buf_ops ; 
 int /*<<< orphan*/  xfs_rmapbt_buf_ops ; 
 int /*<<< orphan*/  xfs_rtbuf_ops ; 
 int /*<<< orphan*/  xfs_sb_buf_ops ; 
 int /*<<< orphan*/  xfs_sb_version_hascrc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_symlink_buf_ops ; 
 int /*<<< orphan*/  xfs_warn (struct xfs_mount*,char*,...) ; 
 scalar_t__ xlog_recover_iodone ; 

__attribute__((used)) static void
xlog_recover_validate_buf_type(
	struct xfs_mount	*mp,
	struct xfs_buf		*bp,
	xfs_buf_log_format_t	*buf_f,
	xfs_lsn_t		current_lsn)
{
	struct xfs_da_blkinfo	*info = bp->b_addr;
	uint32_t		magic32;
	uint16_t		magic16;
	uint16_t		magicda;
	char			*warnmsg = NULL;

	/*
	 * We can only do post recovery validation on items on CRC enabled
	 * fielsystems as we need to know when the buffer was written to be able
	 * to determine if we should have replayed the item. If we replay old
	 * metadata over a newer buffer, then it will enter a temporarily
	 * inconsistent state resulting in verification failures. Hence for now
	 * just avoid the verification stage for non-crc filesystems
	 */
	if (!xfs_sb_version_hascrc(&mp->m_sb))
		return;

	magic32 = be32_to_cpu(*(__be32 *)bp->b_addr);
	magic16 = be16_to_cpu(*(__be16*)bp->b_addr);
	magicda = be16_to_cpu(info->magic);
	switch (xfs_blft_from_flags(buf_f)) {
	case XFS_BLFT_BTREE_BUF:
		switch (magic32) {
		case XFS_ABTB_CRC_MAGIC:
		case XFS_ABTB_MAGIC:
			bp->b_ops = &xfs_bnobt_buf_ops;
			break;
		case XFS_ABTC_CRC_MAGIC:
		case XFS_ABTC_MAGIC:
			bp->b_ops = &xfs_cntbt_buf_ops;
			break;
		case XFS_IBT_CRC_MAGIC:
		case XFS_IBT_MAGIC:
			bp->b_ops = &xfs_inobt_buf_ops;
			break;
		case XFS_FIBT_CRC_MAGIC:
		case XFS_FIBT_MAGIC:
			bp->b_ops = &xfs_finobt_buf_ops;
			break;
		case XFS_BMAP_CRC_MAGIC:
		case XFS_BMAP_MAGIC:
			bp->b_ops = &xfs_bmbt_buf_ops;
			break;
		case XFS_RMAP_CRC_MAGIC:
			bp->b_ops = &xfs_rmapbt_buf_ops;
			break;
		case XFS_REFC_CRC_MAGIC:
			bp->b_ops = &xfs_refcountbt_buf_ops;
			break;
		default:
			warnmsg = "Bad btree block magic!";
			break;
		}
		break;
	case XFS_BLFT_AGF_BUF:
		if (magic32 != XFS_AGF_MAGIC) {
			warnmsg = "Bad AGF block magic!";
			break;
		}
		bp->b_ops = &xfs_agf_buf_ops;
		break;
	case XFS_BLFT_AGFL_BUF:
		if (magic32 != XFS_AGFL_MAGIC) {
			warnmsg = "Bad AGFL block magic!";
			break;
		}
		bp->b_ops = &xfs_agfl_buf_ops;
		break;
	case XFS_BLFT_AGI_BUF:
		if (magic32 != XFS_AGI_MAGIC) {
			warnmsg = "Bad AGI block magic!";
			break;
		}
		bp->b_ops = &xfs_agi_buf_ops;
		break;
	case XFS_BLFT_UDQUOT_BUF:
	case XFS_BLFT_PDQUOT_BUF:
	case XFS_BLFT_GDQUOT_BUF:
#ifdef CONFIG_XFS_QUOTA
		if (magic16 != XFS_DQUOT_MAGIC) {
			warnmsg = "Bad DQUOT block magic!";
			break;
		}
		bp->b_ops = &xfs_dquot_buf_ops;
#else
		xfs_alert(mp,
	"Trying to recover dquots without QUOTA support built in!");
		ASSERT(0);
#endif
		break;
	case XFS_BLFT_DINO_BUF:
		if (magic16 != XFS_DINODE_MAGIC) {
			warnmsg = "Bad INODE block magic!";
			break;
		}
		bp->b_ops = &xfs_inode_buf_ops;
		break;
	case XFS_BLFT_SYMLINK_BUF:
		if (magic32 != XFS_SYMLINK_MAGIC) {
			warnmsg = "Bad symlink block magic!";
			break;
		}
		bp->b_ops = &xfs_symlink_buf_ops;
		break;
	case XFS_BLFT_DIR_BLOCK_BUF:
		if (magic32 != XFS_DIR2_BLOCK_MAGIC &&
		    magic32 != XFS_DIR3_BLOCK_MAGIC) {
			warnmsg = "Bad dir block magic!";
			break;
		}
		bp->b_ops = &xfs_dir3_block_buf_ops;
		break;
	case XFS_BLFT_DIR_DATA_BUF:
		if (magic32 != XFS_DIR2_DATA_MAGIC &&
		    magic32 != XFS_DIR3_DATA_MAGIC) {
			warnmsg = "Bad dir data magic!";
			break;
		}
		bp->b_ops = &xfs_dir3_data_buf_ops;
		break;
	case XFS_BLFT_DIR_FREE_BUF:
		if (magic32 != XFS_DIR2_FREE_MAGIC &&
		    magic32 != XFS_DIR3_FREE_MAGIC) {
			warnmsg = "Bad dir3 free magic!";
			break;
		}
		bp->b_ops = &xfs_dir3_free_buf_ops;
		break;
	case XFS_BLFT_DIR_LEAF1_BUF:
		if (magicda != XFS_DIR2_LEAF1_MAGIC &&
		    magicda != XFS_DIR3_LEAF1_MAGIC) {
			warnmsg = "Bad dir leaf1 magic!";
			break;
		}
		bp->b_ops = &xfs_dir3_leaf1_buf_ops;
		break;
	case XFS_BLFT_DIR_LEAFN_BUF:
		if (magicda != XFS_DIR2_LEAFN_MAGIC &&
		    magicda != XFS_DIR3_LEAFN_MAGIC) {
			warnmsg = "Bad dir leafn magic!";
			break;
		}
		bp->b_ops = &xfs_dir3_leafn_buf_ops;
		break;
	case XFS_BLFT_DA_NODE_BUF:
		if (magicda != XFS_DA_NODE_MAGIC &&
		    magicda != XFS_DA3_NODE_MAGIC) {
			warnmsg = "Bad da node magic!";
			break;
		}
		bp->b_ops = &xfs_da3_node_buf_ops;
		break;
	case XFS_BLFT_ATTR_LEAF_BUF:
		if (magicda != XFS_ATTR_LEAF_MAGIC &&
		    magicda != XFS_ATTR3_LEAF_MAGIC) {
			warnmsg = "Bad attr leaf magic!";
			break;
		}
		bp->b_ops = &xfs_attr3_leaf_buf_ops;
		break;
	case XFS_BLFT_ATTR_RMT_BUF:
		if (magic32 != XFS_ATTR3_RMT_MAGIC) {
			warnmsg = "Bad attr remote magic!";
			break;
		}
		bp->b_ops = &xfs_attr3_rmt_buf_ops;
		break;
	case XFS_BLFT_SB_BUF:
		if (magic32 != XFS_SB_MAGIC) {
			warnmsg = "Bad SB block magic!";
			break;
		}
		bp->b_ops = &xfs_sb_buf_ops;
		break;
#ifdef CONFIG_XFS_RT
	case XFS_BLFT_RTBITMAP_BUF:
	case XFS_BLFT_RTSUMMARY_BUF:
		/* no magic numbers for verification of RT buffers */
		bp->b_ops = &xfs_rtbuf_ops;
		break;
#endif /* CONFIG_XFS_RT */
	default:
		xfs_warn(mp, "Unknown buffer type %d!",
			 xfs_blft_from_flags(buf_f));
		break;
	}

	/*
	 * Nothing else to do in the case of a NULL current LSN as this means
	 * the buffer is more recent than the change in the log and will be
	 * skipped.
	 */
	if (current_lsn == NULLCOMMITLSN)
		return;

	if (warnmsg) {
		xfs_warn(mp, warnmsg);
		ASSERT(0);
	}

	/*
	 * We must update the metadata LSN of the buffer as it is written out to
	 * ensure that older transactions never replay over this one and corrupt
	 * the buffer. This can occur if log recovery is interrupted at some
	 * point after the current transaction completes, at which point a
	 * subsequent mount starts recovery from the beginning.
	 *
	 * Write verifiers update the metadata LSN from log items attached to
	 * the buffer. Therefore, initialize a bli purely to carry the LSN to
	 * the verifier. We'll clean it up in our ->iodone() callback.
	 */
	if (bp->b_ops) {
		struct xfs_buf_log_item	*bip;

		ASSERT(!bp->b_iodone || bp->b_iodone == xlog_recover_iodone);
		bp->b_iodone = xlog_recover_iodone;
		xfs_buf_item_init(bp, mp);
		bip = bp->b_log_item;
		bip->bli_item.li_lsn = current_lsn;
	}
}