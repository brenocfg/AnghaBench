#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xenix_super_block {int dummy; } ;
struct sysv_sb_info {struct buffer_head* s_bh2; struct buffer_head* s_bh1; int /*<<< orphan*/  s_lock; scalar_t__ s_block_base; struct super_block* s_sb; } ;
struct sysv_inode {int dummy; } ;
struct sysv4_super_block {int dummy; } ;
struct sysv2_super_block {int dummy; } ;
struct super_block {int s_id; int /*<<< orphan*/  s_time_max; scalar_t__ s_time_min; struct sysv_sb_info* s_fs_info; } ;
struct coh_super_block {int dummy; } ;
struct buffer_head {int b_blocknr; } ;
struct TYPE_3__ {unsigned long block; int (* test ) (int /*<<< orphan*/ ,struct buffer_head*) ;} ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int BLOCK_SIZE ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SYSV_SB (struct super_block*) ; 
 int /*<<< orphan*/  U32_MAX ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ complete_read_super (struct super_block*,int,int) ; 
 TYPE_1__* flavours ; 
 int /*<<< orphan*/  kfree (struct sysv_sb_info*) ; 
 struct sysv_sb_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 struct buffer_head* sb_bread (struct super_block*,unsigned long) ; 
 int /*<<< orphan*/  sb_set_blocksize (struct super_block*,int) ; 
 int stub1 (int /*<<< orphan*/ ,struct buffer_head*) ; 

__attribute__((used)) static int sysv_fill_super(struct super_block *sb, void *data, int silent)
{
	struct buffer_head *bh1, *bh = NULL;
	struct sysv_sb_info *sbi;
	unsigned long blocknr;
	int size = 0, i;
	
	BUILD_BUG_ON(1024 != sizeof (struct xenix_super_block));
	BUILD_BUG_ON(512 != sizeof (struct sysv4_super_block));
	BUILD_BUG_ON(512 != sizeof (struct sysv2_super_block));
	BUILD_BUG_ON(500 != sizeof (struct coh_super_block));
	BUILD_BUG_ON(64 != sizeof (struct sysv_inode));

	sbi = kzalloc(sizeof(struct sysv_sb_info), GFP_KERNEL);
	if (!sbi)
		return -ENOMEM;

	sbi->s_sb = sb;
	sbi->s_block_base = 0;
	mutex_init(&sbi->s_lock);
	sb->s_fs_info = sbi;
	sb->s_time_min = 0;
	sb->s_time_max = U32_MAX;
	sb_set_blocksize(sb, BLOCK_SIZE);

	for (i = 0; i < ARRAY_SIZE(flavours) && !size; i++) {
		brelse(bh);
		bh = sb_bread(sb, flavours[i].block);
		if (!bh)
			continue;
		size = flavours[i].test(SYSV_SB(sb), bh);
	}

	if (!size)
		goto Eunknown;

	switch (size) {
		case 1:
			blocknr = bh->b_blocknr << 1;
			brelse(bh);
			sb_set_blocksize(sb, 512);
			bh1 = sb_bread(sb, blocknr);
			bh = sb_bread(sb, blocknr + 1);
			break;
		case 2:
			bh1 = bh;
			break;
		case 3:
			blocknr = bh->b_blocknr >> 1;
			brelse(bh);
			sb_set_blocksize(sb, 2048);
			bh1 = bh = sb_bread(sb, blocknr);
			break;
		default:
			goto Ebadsize;
	}

	if (bh && bh1) {
		sbi->s_bh1 = bh1;
		sbi->s_bh2 = bh;
		if (complete_read_super(sb, silent, size))
			return 0;
	}

	brelse(bh1);
	brelse(bh);
	sb_set_blocksize(sb, BLOCK_SIZE);
	printk("oldfs: cannot read superblock\n");
failed:
	kfree(sbi);
	return -EINVAL;

Eunknown:
	brelse(bh);
	if (!silent)
		printk("VFS: unable to find oldfs superblock on device %s\n",
			sb->s_id);
	goto failed;
Ebadsize:
	brelse(bh);
	if (!silent)
		printk("VFS: oldfs: unsupported block size (%dKb)\n",
			1<<(size-2));
	goto failed;
}