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
typedef  int u64 ;
struct super_block {int s_blocksize_bits; int s_blocksize; struct qnx6_sb_info* s_fs_info; int /*<<< orphan*/ * s_root; int /*<<< orphan*/  s_time_max; scalar_t__ s_time_min; int /*<<< orphan*/  s_flags; scalar_t__ s_magic; int /*<<< orphan*/ * s_op; } ;
struct TYPE_2__ {scalar_t__ levels; } ;
struct qnx6_super_block {TYPE_1__ Longfile; TYPE_1__ Inode; int /*<<< orphan*/  sb_serial; int /*<<< orphan*/  sb_checksum; int /*<<< orphan*/  sb_magic; int /*<<< orphan*/  sb_num_blocks; int /*<<< orphan*/  sb_blocksize; } ;
struct qnx6_sb_info {int s_blks_off; void* inodes; void* longfile; int /*<<< orphan*/  s_ptrbits; struct qnx6_super_block* sb; struct buffer_head* sb_buf; int /*<<< orphan*/  s_bytesex; } ;
struct inode {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BYTESEX_LE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int /*<<< orphan*/  MMI_FS ; 
 int PTR_ERR (struct inode*) ; 
 int QNX6_BOOTBLOCK_SIZE ; 
 scalar_t__ QNX6_PTR_MAX_LEVELS ; 
 int /*<<< orphan*/  QNX6_ROOT_INO ; 
 struct qnx6_sb_info* QNX6_SB (struct super_block*) ; 
 int QNX6_SUPERBLOCK_AREA ; 
 int QNX6_SUPERBLOCK_SIZE ; 
 scalar_t__ QNX6_SUPER_MAGIC ; 
 int /*<<< orphan*/  SB_RDONLY ; 
 int /*<<< orphan*/  U32_MAX ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ crc32_be (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * d_make_root (struct inode*) ; 
 int /*<<< orphan*/  dput (int /*<<< orphan*/ *) ; 
 scalar_t__ fs32_to_cpu (struct qnx6_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ fs64_to_cpu (struct qnx6_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ilog2 (int) ; 
 int /*<<< orphan*/  iput (void*) ; 
 int /*<<< orphan*/  kfree (struct qnx6_sb_info*) ; 
 struct qnx6_sb_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 struct buffer_head* qnx6_check_first_superblock (struct super_block*,int,int) ; 
 char* qnx6_checkroot (struct super_block*) ; 
 struct inode* qnx6_iget (struct super_block*,int /*<<< orphan*/ ) ; 
 struct qnx6_super_block* qnx6_mmi_fill_super (struct super_block*,int) ; 
 int /*<<< orphan*/  qnx6_parse_options (char*,struct super_block*) ; 
 void* qnx6_private_inode (struct super_block*,TYPE_1__*) ; 
 int /*<<< orphan*/  qnx6_sops ; 
 int /*<<< orphan*/  qnx6_superblock_debug (struct qnx6_super_block*,struct super_block*) ; 
 struct buffer_head* sb_bread (struct super_block*,int) ; 
 int /*<<< orphan*/  sb_set_blocksize (struct super_block*,scalar_t__) ; 
 scalar_t__ test_opt (struct super_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qnx6_fill_super(struct super_block *s, void *data, int silent)
{
	struct buffer_head *bh1 = NULL, *bh2 = NULL;
	struct qnx6_super_block *sb1 = NULL, *sb2 = NULL;
	struct qnx6_sb_info *sbi;
	struct inode *root;
	const char *errmsg;
	struct qnx6_sb_info *qs;
	int ret = -EINVAL;
	u64 offset;
	int bootblock_offset = QNX6_BOOTBLOCK_SIZE;

	qs = kzalloc(sizeof(struct qnx6_sb_info), GFP_KERNEL);
	if (!qs)
		return -ENOMEM;
	s->s_fs_info = qs;

	/* Superblock always is 512 Byte long */
	if (!sb_set_blocksize(s, QNX6_SUPERBLOCK_SIZE)) {
		pr_err("unable to set blocksize\n");
		goto outnobh;
	}

	/* parse the mount-options */
	if (!qnx6_parse_options((char *) data, s)) {
		pr_err("invalid mount options.\n");
		goto outnobh;
	}
	if (test_opt(s, MMI_FS)) {
		sb1 = qnx6_mmi_fill_super(s, silent);
		if (sb1)
			goto mmi_success;
		else
			goto outnobh;
	}
	sbi = QNX6_SB(s);
	sbi->s_bytesex = BYTESEX_LE;
	/* Check the superblock signatures
	   start with the first superblock */
	bh1 = qnx6_check_first_superblock(s,
		bootblock_offset / QNX6_SUPERBLOCK_SIZE, silent);
	if (!bh1) {
		/* try again without bootblock offset */
		bh1 = qnx6_check_first_superblock(s, 0, silent);
		if (!bh1) {
			pr_err("unable to read the first superblock\n");
			goto outnobh;
		}
		/* seems that no bootblock at partition start */
		bootblock_offset = 0;
	}
	sb1 = (struct qnx6_super_block *)bh1->b_data;

#ifdef CONFIG_QNX6FS_DEBUG
	qnx6_superblock_debug(sb1, s);
#endif

	/* checksum check - start at byte 8 and end at byte 512 */
	if (fs32_to_cpu(sbi, sb1->sb_checksum) !=
			crc32_be(0, (char *)(bh1->b_data + 8), 504)) {
		pr_err("superblock #1 checksum error\n");
		goto out;
	}

	/* set new blocksize */
	if (!sb_set_blocksize(s, fs32_to_cpu(sbi, sb1->sb_blocksize))) {
		pr_err("unable to set blocksize\n");
		goto out;
	}
	/* blocksize invalidates bh - pull it back in */
	brelse(bh1);
	bh1 = sb_bread(s, bootblock_offset >> s->s_blocksize_bits);
	if (!bh1)
		goto outnobh;
	sb1 = (struct qnx6_super_block *)bh1->b_data;

	/* calculate second superblock blocknumber */
	offset = fs32_to_cpu(sbi, sb1->sb_num_blocks) +
		(bootblock_offset >> s->s_blocksize_bits) +
		(QNX6_SUPERBLOCK_AREA >> s->s_blocksize_bits);

	/* set bootblock offset */
	sbi->s_blks_off = (bootblock_offset >> s->s_blocksize_bits) +
			  (QNX6_SUPERBLOCK_AREA >> s->s_blocksize_bits);

	/* next the second superblock */
	bh2 = sb_bread(s, offset);
	if (!bh2) {
		pr_err("unable to read the second superblock\n");
		goto out;
	}
	sb2 = (struct qnx6_super_block *)bh2->b_data;
	if (fs32_to_cpu(sbi, sb2->sb_magic) != QNX6_SUPER_MAGIC) {
		if (!silent)
			pr_err("wrong signature (magic) in superblock #2.\n");
		goto out;
	}

	/* checksum check - start at byte 8 and end at byte 512 */
	if (fs32_to_cpu(sbi, sb2->sb_checksum) !=
				crc32_be(0, (char *)(bh2->b_data + 8), 504)) {
		pr_err("superblock #2 checksum error\n");
		goto out;
	}

	if (fs64_to_cpu(sbi, sb1->sb_serial) >=
					fs64_to_cpu(sbi, sb2->sb_serial)) {
		/* superblock #1 active */
		sbi->sb_buf = bh1;
		sbi->sb = (struct qnx6_super_block *)bh1->b_data;
		brelse(bh2);
		pr_info("superblock #1 active\n");
	} else {
		/* superblock #2 active */
		sbi->sb_buf = bh2;
		sbi->sb = (struct qnx6_super_block *)bh2->b_data;
		brelse(bh1);
		pr_info("superblock #2 active\n");
	}
mmi_success:
	/* sanity check - limit maximum indirect pointer levels */
	if (sb1->Inode.levels > QNX6_PTR_MAX_LEVELS) {
		pr_err("too many inode levels (max %i, sb %i)\n",
		       QNX6_PTR_MAX_LEVELS, sb1->Inode.levels);
		goto out;
	}
	if (sb1->Longfile.levels > QNX6_PTR_MAX_LEVELS) {
		pr_err("too many longfilename levels (max %i, sb %i)\n",
		       QNX6_PTR_MAX_LEVELS, sb1->Longfile.levels);
		goto out;
	}
	s->s_op = &qnx6_sops;
	s->s_magic = QNX6_SUPER_MAGIC;
	s->s_flags |= SB_RDONLY;        /* Yup, read-only yet */
	s->s_time_min = 0;
	s->s_time_max = U32_MAX;

	/* ease the later tree level calculations */
	sbi = QNX6_SB(s);
	sbi->s_ptrbits = ilog2(s->s_blocksize / 4);
	sbi->inodes = qnx6_private_inode(s, &sb1->Inode);
	if (!sbi->inodes)
		goto out;
	sbi->longfile = qnx6_private_inode(s, &sb1->Longfile);
	if (!sbi->longfile)
		goto out1;

	/* prefetch root inode */
	root = qnx6_iget(s, QNX6_ROOT_INO);
	if (IS_ERR(root)) {
		pr_err("get inode failed\n");
		ret = PTR_ERR(root);
		goto out2;
	}

	ret = -ENOMEM;
	s->s_root = d_make_root(root);
	if (!s->s_root)
		goto out2;

	ret = -EINVAL;
	errmsg = qnx6_checkroot(s);
	if (errmsg != NULL) {
		if (!silent)
			pr_err("%s\n", errmsg);
		goto out3;
	}
	return 0;

out3:
	dput(s->s_root);
	s->s_root = NULL;
out2:
	iput(sbi->longfile);
out1:
	iput(sbi->inodes);
out:
	if (bh1)
		brelse(bh1);
	if (bh2)
		brelse(bh2);
outnobh:
	kfree(qs);
	s->s_fs_info = NULL;
	return ret;
}