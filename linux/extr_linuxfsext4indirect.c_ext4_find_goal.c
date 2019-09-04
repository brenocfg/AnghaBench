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
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  ext4_lblk_t ;
typedef  int ext4_fsblk_t ;
typedef  int /*<<< orphan*/  Indirect ;

/* Variables and functions */
 int EXT4_MAX_BLOCK_FILE_PHYS ; 
 int ext4_find_near (struct inode*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ext4_fsblk_t ext4_find_goal(struct inode *inode, ext4_lblk_t block,
				   Indirect *partial)
{
	ext4_fsblk_t goal;

	/*
	 * XXX need to get goal block from mballoc's data structures
	 */

	goal = ext4_find_near(inode, partial);
	goal = goal & EXT4_MAX_BLOCK_FILE_PHYS;
	return goal;
}