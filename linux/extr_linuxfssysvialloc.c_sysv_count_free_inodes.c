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
struct sysv_sb_info {int s_ninodes; int s_inodes_per_block_1; int /*<<< orphan*/ * s_sb_total_free_inodes; int /*<<< orphan*/  s_lock; } ;
struct sysv_inode {scalar_t__ i_mode; scalar_t__ i_nlink; } ;
struct super_block {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int SYSV_ROOT_INO ; 
 struct sysv_sb_info* SYSV_SB (struct super_block*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  cpu_to_fs16 (struct sysv_sb_info*,int) ; 
 int /*<<< orphan*/  dirty_sb (struct super_block*) ; 
 int fs16_to_cpu (struct sysv_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  sb_rdonly (struct super_block*) ; 
 struct sysv_inode* sysv_raw_inode (struct super_block*,int,struct buffer_head**) ; 

unsigned long sysv_count_free_inodes(struct super_block * sb)
{
	struct sysv_sb_info *sbi = SYSV_SB(sb);
	struct buffer_head * bh;
	struct sysv_inode * raw_inode;
	int ino, count, sb_count;

	mutex_lock(&sbi->s_lock);

	sb_count = fs16_to_cpu(sbi, *sbi->s_sb_total_free_inodes);

	if (0)
		goto trust_sb;

	/* this causes a lot of disk traffic ... */
	count = 0;
	ino = SYSV_ROOT_INO+1;
	raw_inode = sysv_raw_inode(sb, ino, &bh);
	if (!raw_inode)
		goto Eio;
	while (ino <= sbi->s_ninodes) {
		if (raw_inode->i_mode == 0 && raw_inode->i_nlink == 0)
			count++;
		if ((ino++ & sbi->s_inodes_per_block_1) == 0) {
			brelse(bh);
			raw_inode = sysv_raw_inode(sb, ino, &bh);
			if (!raw_inode)
				goto Eio;
		} else
			raw_inode++;
	}
	brelse(bh);
	if (count != sb_count)
		goto Einval;
out:
	mutex_unlock(&sbi->s_lock);
	return count;

Einval:
	printk("sysv_count_free_inodes: "
		"free inode count was %d, correcting to %d\n",
		sb_count, count);
	if (!sb_rdonly(sb)) {
		*sbi->s_sb_total_free_inodes = cpu_to_fs16(SYSV_SB(sb), count);
		dirty_sb(sb);
	}
	goto out;

Eio:
	printk("sysv_count_free_inodes: unable to read inode table\n");
trust_sb:
	count = sb_count;
	goto out;
}