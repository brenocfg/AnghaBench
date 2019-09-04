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

/* Variables and functions */
 int OCFS2_SUBALLOC_ALLOC ; 

__attribute__((used)) static inline int ocfs2_calc_group_alloc_credits(struct super_block *sb,
						 unsigned int cpg)
{
	int blocks;
	int bitmap_blocks = OCFS2_SUBALLOC_ALLOC + 1;
	/* parent inode update + new block group header + bitmap inode update
	   + bitmap blocks affected */
	blocks = 1 + 1 + 1 + bitmap_blocks;
	return blocks;
}