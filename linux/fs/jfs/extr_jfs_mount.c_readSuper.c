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
struct super_block {int s_blocksize_bits; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int SUPER1_OFF ; 
 int SUPER2_OFF ; 
 struct buffer_head* sb_bread (struct super_block*,int) ; 

int readSuper(struct super_block *sb, struct buffer_head **bpp)
{
	/* read in primary superblock */
	*bpp = sb_bread(sb, SUPER1_OFF >> sb->s_blocksize_bits);
	if (*bpp)
		return 0;

	/* read in secondary/replicated superblock */
	*bpp = sb_bread(sb, SUPER2_OFF >> sb->s_blocksize_bits);
	if (*bpp)
		return 0;

	return -EIO;
}