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
struct super_block {scalar_t__ s_bdev; scalar_t__ s_mtd; } ;

/* Variables and functions */
 int EIO ; 
 int ENAMETOOLONG ; 
 size_t ROMFS_MAXFN ; 
 int romfs_blk_strcmp (struct super_block*,unsigned long,char const*,size_t) ; 
 size_t romfs_maxsize (struct super_block*) ; 
 int romfs_mtd_strcmp (struct super_block*,unsigned long,char const*,size_t) ; 

int romfs_dev_strcmp(struct super_block *sb, unsigned long pos,
		     const char *str, size_t size)
{
	size_t limit;

	limit = romfs_maxsize(sb);
	if (pos >= limit)
		return -EIO;
	if (size > ROMFS_MAXFN)
		return -ENAMETOOLONG;
	if (size + 1 > limit - pos)
		return -EIO;

#ifdef CONFIG_ROMFS_ON_MTD
	if (sb->s_mtd)
		return romfs_mtd_strcmp(sb, pos, str, size);
#endif
#ifdef CONFIG_ROMFS_ON_BLOCK
	if (sb->s_bdev)
		return romfs_blk_strcmp(sb, pos, str, size);
#endif
	return -EIO;
}