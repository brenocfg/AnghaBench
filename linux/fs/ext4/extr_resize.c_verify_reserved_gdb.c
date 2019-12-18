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
struct buffer_head {scalar_t__ b_blocknr; scalar_t__ b_data; } ;
typedef  unsigned int ext4_group_t ;
typedef  scalar_t__ ext4_fsblk_t ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int EFBIG ; 
 int EINVAL ; 
 int EXT4_ADDR_PER_BLOCK (struct super_block*) ; 
 unsigned int EXT4_BLOCKS_PER_GROUP (struct super_block*) ; 
 unsigned int ext4_list_backups (struct super_block*,unsigned int*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  ext4_warning (struct super_block*,char*,scalar_t__ const,unsigned int,scalar_t__ const) ; 
 scalar_t__ const le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int verify_reserved_gdb(struct super_block *sb,
			       ext4_group_t end,
			       struct buffer_head *primary)
{
	const ext4_fsblk_t blk = primary->b_blocknr;
	unsigned three = 1;
	unsigned five = 5;
	unsigned seven = 7;
	unsigned grp;
	__le32 *p = (__le32 *)primary->b_data;
	int gdbackups = 0;

	while ((grp = ext4_list_backups(sb, &three, &five, &seven)) < end) {
		if (le32_to_cpu(*p++) !=
		    grp * EXT4_BLOCKS_PER_GROUP(sb) + blk){
			ext4_warning(sb, "reserved GDT %llu"
				     " missing grp %d (%llu)",
				     blk, grp,
				     grp *
				     (ext4_fsblk_t)EXT4_BLOCKS_PER_GROUP(sb) +
				     blk);
			return -EINVAL;
		}
		if (++gdbackups > EXT4_ADDR_PER_BLOCK(sb))
			return -EFBIG;
	}

	return gdbackups;
}