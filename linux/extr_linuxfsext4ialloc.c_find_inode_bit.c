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
struct super_block {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  ext4_group_t ;
struct TYPE_2__ {int /*<<< orphan*/ * s_journal; } ;

/* Variables and functions */
 unsigned long EXT4_INODES_PER_GROUP (struct super_block*) ; 
 TYPE_1__* EXT4_SB (struct super_block*) ; 
 unsigned long ext4_find_next_zero_bit (unsigned long*,unsigned long,unsigned long) ; 
 scalar_t__ recently_deleted (struct super_block*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int find_inode_bit(struct super_block *sb, ext4_group_t group,
			  struct buffer_head *bitmap, unsigned long *ino)
{
next:
	*ino = ext4_find_next_zero_bit((unsigned long *)
				       bitmap->b_data,
				       EXT4_INODES_PER_GROUP(sb), *ino);
	if (*ino >= EXT4_INODES_PER_GROUP(sb))
		return 0;

	if ((EXT4_SB(sb)->s_journal == NULL) &&
	    recently_deleted(sb, group, *ino)) {
		*ino = *ino + 1;
		if (*ino < EXT4_INODES_PER_GROUP(sb))
			goto next;
		return 0;
	}

	return 1;
}