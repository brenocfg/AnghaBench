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
struct super_block {int dummy; } ;
struct f2fs_super_block {int dummy; } ;
struct f2fs_sb_info {struct super_block* sb; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 scalar_t__ F2FS_SUPER_OFFSET ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  f2fs_msg (struct super_block*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kfree (struct f2fs_super_block*) ; 
 struct f2fs_super_block* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct f2fs_super_block*,scalar_t__,int) ; 
 scalar_t__ sanity_check_raw_super (struct f2fs_sb_info*,struct buffer_head*) ; 
 struct buffer_head* sb_bread (struct super_block*,int) ; 

__attribute__((used)) static int read_raw_super_block(struct f2fs_sb_info *sbi,
			struct f2fs_super_block **raw_super,
			int *valid_super_block, int *recovery)
{
	struct super_block *sb = sbi->sb;
	int block;
	struct buffer_head *bh;
	struct f2fs_super_block *super;
	int err = 0;

	super = kzalloc(sizeof(struct f2fs_super_block), GFP_KERNEL);
	if (!super)
		return -ENOMEM;

	for (block = 0; block < 2; block++) {
		bh = sb_bread(sb, block);
		if (!bh) {
			f2fs_msg(sb, KERN_ERR, "Unable to read %dth superblock",
				block + 1);
			err = -EIO;
			continue;
		}

		/* sanity checking of raw super */
		if (sanity_check_raw_super(sbi, bh)) {
			f2fs_msg(sb, KERN_ERR,
				"Can't find valid F2FS filesystem in %dth superblock",
				block + 1);
			err = -EINVAL;
			brelse(bh);
			continue;
		}

		if (!*raw_super) {
			memcpy(super, bh->b_data + F2FS_SUPER_OFFSET,
							sizeof(*super));
			*valid_super_block = block;
			*raw_super = super;
		}
		brelse(bh);
	}

	/* Fail to read any one of the superblocks*/
	if (err < 0)
		*recovery = 1;

	/* No valid superblock */
	if (!*raw_super)
		kfree(super);
	else
		err = 0;

	return err;
}