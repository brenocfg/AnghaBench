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
struct super_block {int s_blocksize; int /*<<< orphan*/  s_id; } ;
struct minix_sb_info {int s_ninodes; int s_imap_blocks; int s_zmap_blocks; } ;
struct minix2_inode {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int ino_t ;

/* Variables and functions */
 struct minix_sb_info* minix_sb (struct super_block*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 struct buffer_head* sb_bread (struct super_block*,int) ; 

struct minix2_inode *
minix_V2_raw_inode(struct super_block *sb, ino_t ino, struct buffer_head **bh)
{
	int block;
	struct minix_sb_info *sbi = minix_sb(sb);
	struct minix2_inode *p;
	int minix2_inodes_per_block = sb->s_blocksize / sizeof(struct minix2_inode);

	*bh = NULL;
	if (!ino || ino > sbi->s_ninodes) {
		printk("Bad inode number on dev %s: %ld is out of range\n",
		       sb->s_id, (long)ino);
		return NULL;
	}
	ino--;
	block = 2 + sbi->s_imap_blocks + sbi->s_zmap_blocks +
		 ino / minix2_inodes_per_block;
	*bh = sb_bread(sb, block);
	if (!*bh) {
		printk("Unable to read inode block\n");
		return NULL;
	}
	p = (void *)(*bh)->b_data;
	return p + ino % minix2_inodes_per_block;
}