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
struct super_block {int s_blocksize; } ;
struct qnx6_super_block {int /*<<< orphan*/  sb_magic; } ;
struct qnx6_sb_info {int /*<<< orphan*/  s_bytesex; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BYTESEX_BE ; 
 int /*<<< orphan*/  BYTESEX_LE ; 
 struct qnx6_sb_info* QNX6_SB (struct super_block*) ; 
 scalar_t__ QNX6_SUPER_MAGIC ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ fs32_to_cpu (struct qnx6_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 struct buffer_head* sb_bread (struct super_block*,int) ; 

__attribute__((used)) static struct buffer_head *qnx6_check_first_superblock(struct super_block *s,
				int offset, int silent)
{
	struct qnx6_sb_info *sbi = QNX6_SB(s);
	struct buffer_head *bh;
	struct qnx6_super_block *sb;

	/* Check the superblock signatures
	   start with the first superblock */
	bh = sb_bread(s, offset);
	if (!bh) {
		pr_err("unable to read the first superblock\n");
		return NULL;
	}
	sb = (struct qnx6_super_block *)bh->b_data;
	if (fs32_to_cpu(sbi, sb->sb_magic) != QNX6_SUPER_MAGIC) {
		sbi->s_bytesex = BYTESEX_BE;
		if (fs32_to_cpu(sbi, sb->sb_magic) == QNX6_SUPER_MAGIC) {
			/* we got a big endian fs */
			pr_debug("fs got different endianness.\n");
			return bh;
		} else
			sbi->s_bytesex = BYTESEX_LE;
		if (!silent) {
			if (offset == 0) {
				pr_err("wrong signature (magic) in superblock #1.\n");
			} else {
				pr_info("wrong signature (magic) at position (0x%lx) - will try alternative position (0x0000).\n",
					offset * s->s_blocksize);
			}
		}
		brelse(bh);
		return NULL;
	}
	return bh;
}