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
typedef  unsigned int u64 ;
struct super_block {int s_blocksize; } ;
struct omfs_sb_info {unsigned int s_imap_size; int /*<<< orphan*/  s_bitmap_lock; } ;

/* Variables and functions */
 struct omfs_sb_info* OMFS_SB (struct super_block*) ; 
 unsigned int do_div (unsigned int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int set_run (struct super_block*,unsigned int,int,unsigned int,int,int /*<<< orphan*/ ) ; 

int omfs_clear_range(struct super_block *sb, u64 block, int count)
{
	struct omfs_sb_info *sbi = OMFS_SB(sb);
	int bits_per_entry = 8 * sb->s_blocksize;
	u64 tmp;
	unsigned int map, bit;
	int ret;

	tmp = block;
	bit = do_div(tmp, bits_per_entry);
	map = tmp;

	if (map >= sbi->s_imap_size)
		return 0;

	mutex_lock(&sbi->s_bitmap_lock);
	ret = set_run(sb, map, bits_per_entry, bit, count, 0);
	mutex_unlock(&sbi->s_bitmap_lock);
	return ret;
}