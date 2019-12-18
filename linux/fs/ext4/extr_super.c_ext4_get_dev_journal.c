#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct super_block {int s_blocksize; int /*<<< orphan*/  s_bdev; } ;
struct ext4_super_block {scalar_t__ s_checksum; int /*<<< orphan*/  s_uuid; int /*<<< orphan*/  s_feature_ro_compat; int /*<<< orphan*/  s_feature_incompat; int /*<<< orphan*/  s_magic; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct block_device {int dummy; } ;
struct TYPE_11__ {TYPE_2__* j_superblock; int /*<<< orphan*/  j_sb_buffer; struct super_block* j_private; } ;
typedef  TYPE_3__ journal_t ;
typedef  int ext4_fsblk_t ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_12__ {struct block_device* journal_bdev; TYPE_1__* s_es; } ;
struct TYPE_10__ {int /*<<< orphan*/  s_nr_users; } ;
struct TYPE_9__ {int /*<<< orphan*/  s_journal_uuid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EXT4_FEATURE_INCOMPAT_JOURNAL_DEV ; 
 int EXT4_FEATURE_RO_COMPAT_METADATA_CSUM ; 
 int EXT4_MIN_BLOCK_SIZE ; 
 TYPE_8__* EXT4_SB (struct super_block*) ; 
 scalar_t__ EXT4_SUPER_MAGIC ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int REQ_META ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int REQ_PRIO ; 
 struct buffer_head* __bread (struct block_device*,int,int) ; 
 int bdev_logical_block_size (struct block_device*) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_uptodate (int /*<<< orphan*/ ) ; 
 struct block_device* ext4_blkdev_get (int /*<<< orphan*/ ,struct super_block*) ; 
 int /*<<< orphan*/  ext4_blkdev_put (struct block_device*) ; 
 int ext4_blocks_count (struct ext4_super_block*) ; 
 int /*<<< orphan*/  ext4_has_feature_journal (struct super_block*) ; 
 int /*<<< orphan*/  ext4_init_journal_params (struct super_block*,TYPE_3__*) ; 
 int /*<<< orphan*/  ext4_msg (struct super_block*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ext4_superblock_csum (struct super_block*,struct ext4_super_block*) ; 
 int /*<<< orphan*/  jbd2_journal_destroy (TYPE_3__*) ; 
 TYPE_3__* jbd2_journal_init_dev (struct block_device*,int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ll_rw_block (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_blocksize (struct block_device*,int) ; 
 int /*<<< orphan*/  wait_on_buffer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static journal_t *ext4_get_dev_journal(struct super_block *sb,
				       dev_t j_dev)
{
	struct buffer_head *bh;
	journal_t *journal;
	ext4_fsblk_t start;
	ext4_fsblk_t len;
	int hblock, blocksize;
	ext4_fsblk_t sb_block;
	unsigned long offset;
	struct ext4_super_block *es;
	struct block_device *bdev;

	BUG_ON(!ext4_has_feature_journal(sb));

	bdev = ext4_blkdev_get(j_dev, sb);
	if (bdev == NULL)
		return NULL;

	blocksize = sb->s_blocksize;
	hblock = bdev_logical_block_size(bdev);
	if (blocksize < hblock) {
		ext4_msg(sb, KERN_ERR,
			"blocksize too small for journal device");
		goto out_bdev;
	}

	sb_block = EXT4_MIN_BLOCK_SIZE / blocksize;
	offset = EXT4_MIN_BLOCK_SIZE % blocksize;
	set_blocksize(bdev, blocksize);
	if (!(bh = __bread(bdev, sb_block, blocksize))) {
		ext4_msg(sb, KERN_ERR, "couldn't read superblock of "
		       "external journal");
		goto out_bdev;
	}

	es = (struct ext4_super_block *) (bh->b_data + offset);
	if ((le16_to_cpu(es->s_magic) != EXT4_SUPER_MAGIC) ||
	    !(le32_to_cpu(es->s_feature_incompat) &
	      EXT4_FEATURE_INCOMPAT_JOURNAL_DEV)) {
		ext4_msg(sb, KERN_ERR, "external journal has "
					"bad superblock");
		brelse(bh);
		goto out_bdev;
	}

	if ((le32_to_cpu(es->s_feature_ro_compat) &
	     EXT4_FEATURE_RO_COMPAT_METADATA_CSUM) &&
	    es->s_checksum != ext4_superblock_csum(sb, es)) {
		ext4_msg(sb, KERN_ERR, "external journal has "
				       "corrupt superblock");
		brelse(bh);
		goto out_bdev;
	}

	if (memcmp(EXT4_SB(sb)->s_es->s_journal_uuid, es->s_uuid, 16)) {
		ext4_msg(sb, KERN_ERR, "journal UUID does not match");
		brelse(bh);
		goto out_bdev;
	}

	len = ext4_blocks_count(es);
	start = sb_block + 1;
	brelse(bh);	/* we're done with the superblock */

	journal = jbd2_journal_init_dev(bdev, sb->s_bdev,
					start, len, blocksize);
	if (!journal) {
		ext4_msg(sb, KERN_ERR, "failed to create device journal");
		goto out_bdev;
	}
	journal->j_private = sb;
	ll_rw_block(REQ_OP_READ, REQ_META | REQ_PRIO, 1, &journal->j_sb_buffer);
	wait_on_buffer(journal->j_sb_buffer);
	if (!buffer_uptodate(journal->j_sb_buffer)) {
		ext4_msg(sb, KERN_ERR, "I/O error on journal device");
		goto out_journal;
	}
	if (be32_to_cpu(journal->j_superblock->s_nr_users) != 1) {
		ext4_msg(sb, KERN_ERR, "External journal has more than one "
					"user (unsupported) - %d",
			be32_to_cpu(journal->j_superblock->s_nr_users));
		goto out_journal;
	}
	EXT4_SB(sb)->journal_bdev = bdev;
	ext4_init_journal_params(sb, journal);
	return journal;

out_journal:
	jbd2_journal_destroy(journal);
out_bdev:
	ext4_blkdev_put(bdev);
	return NULL;
}