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
struct sysv_sb_info {int s_firstinodezone; int s_block_base; unsigned int s_inodes_per_block_bits; unsigned int s_inodes_per_block_1; } ;
struct sysv_inode {int dummy; } ;
struct super_block {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 struct sysv_sb_info* SYSV_SB (struct super_block*) ; 
 struct buffer_head* sb_bread (struct super_block*,int) ; 

struct sysv_inode *
sysv_raw_inode(struct super_block *sb, unsigned ino, struct buffer_head **bh)
{
	struct sysv_sb_info *sbi = SYSV_SB(sb);
	struct sysv_inode *res;
	int block = sbi->s_firstinodezone + sbi->s_block_base;

	block += (ino-1) >> sbi->s_inodes_per_block_bits;
	*bh = sb_bread(sb, block);
	if (!*bh)
		return NULL;
	res = (struct sysv_inode *)(*bh)->b_data;
	return res + ((ino-1) & sbi->s_inodes_per_block_1);
}