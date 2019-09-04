#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct super_block {int /*<<< orphan*/  s_uuid; } ;
struct erofs_super_block {unsigned int blkszbits; int /*<<< orphan*/  volume_name; int /*<<< orphan*/  uuid; int /*<<< orphan*/  build_time_nsec; int /*<<< orphan*/  build_time; int /*<<< orphan*/  inos; int /*<<< orphan*/  root_nid; int /*<<< orphan*/  meta_blkaddr; int /*<<< orphan*/  blocks; int /*<<< orphan*/  magic; } ;
struct erofs_sb_info {int /*<<< orphan*/ * volume_name; scalar_t__ build_time_nsec; void* build_time; void* inos; int /*<<< orphan*/  root_nid; scalar_t__ islotbits; scalar_t__ meta_blkaddr; scalar_t__ blocks; } ;
struct erofs_inode_v1 {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 struct erofs_sb_info* EROFS_SB (struct super_block*) ; 
 scalar_t__ EROFS_SUPER_MAGIC_V1 ; 
 int EROFS_SUPER_OFFSET ; 
 unsigned int LOG_BLOCK_SIZE ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  errln (char*,...) ; 
 scalar_t__ ffs (int) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 void* le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct buffer_head* sb_bread (struct super_block*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int superblock_read(struct super_block *sb)
{
	struct erofs_sb_info *sbi;
	struct buffer_head *bh;
	struct erofs_super_block *layout;
	unsigned blkszbits;
	int ret;

	bh = sb_bread(sb, 0);

	if (bh == NULL) {
		errln("cannot read erofs superblock");
		return -EIO;
	}

	sbi = EROFS_SB(sb);
	layout = (struct erofs_super_block *)((u8 *)bh->b_data
		 + EROFS_SUPER_OFFSET);

	ret = -EINVAL;
	if (le32_to_cpu(layout->magic) != EROFS_SUPER_MAGIC_V1) {
		errln("cannot find valid erofs superblock");
		goto out;
	}

	blkszbits = layout->blkszbits;
	/* 9(512 bytes) + LOG_SECTORS_PER_BLOCK == LOG_BLOCK_SIZE */
	if (unlikely(blkszbits != LOG_BLOCK_SIZE)) {
		errln("blksize %u isn't supported on this platform",
			1 << blkszbits);
		goto out;
	}

	sbi->blocks = le32_to_cpu(layout->blocks);
	sbi->meta_blkaddr = le32_to_cpu(layout->meta_blkaddr);
#ifdef CONFIG_EROFS_FS_XATTR
	sbi->xattr_blkaddr = le32_to_cpu(layout->xattr_blkaddr);
#endif
	sbi->islotbits = ffs(sizeof(struct erofs_inode_v1)) - 1;
#ifdef CONFIG_EROFS_FS_ZIP
	sbi->clusterbits = 12;

	if (1 << (sbi->clusterbits - 12) > Z_EROFS_CLUSTER_MAX_PAGES)
		errln("clusterbits %u is not supported on this kernel",
			sbi->clusterbits);
#endif

	sbi->root_nid = le16_to_cpu(layout->root_nid);
	sbi->inos = le64_to_cpu(layout->inos);

	sbi->build_time = le64_to_cpu(layout->build_time);
	sbi->build_time_nsec = le32_to_cpu(layout->build_time_nsec);

	memcpy(&sb->s_uuid, layout->uuid, sizeof(layout->uuid));
	memcpy(sbi->volume_name, layout->volume_name,
		sizeof(layout->volume_name));

	ret = 0;
out:
	brelse(bh);
	return ret;
}