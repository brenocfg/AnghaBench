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
typedef  scalar_t__ sysv_zone_t ;
struct super_block {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYSV_SB (struct super_block*) ; 
 int /*<<< orphan*/  bforget (struct buffer_head*) ; 
 scalar_t__* block_end (struct buffer_head*) ; 
 int block_to_cpu (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  free_data (struct inode*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 struct buffer_head* sb_bread (struct super_block*,int) ; 
 int /*<<< orphan*/  sysv_free_block (struct super_block*,scalar_t__) ; 

__attribute__((used)) static void free_branches(struct inode *inode, sysv_zone_t *p, sysv_zone_t *q, int depth)
{
	struct buffer_head * bh;
	struct super_block *sb = inode->i_sb;

	if (depth--) {
		for ( ; p < q ; p++) {
			int block;
			sysv_zone_t nr = *p;
			if (!nr)
				continue;
			*p = 0;
			block = block_to_cpu(SYSV_SB(sb), nr);
			bh = sb_bread(sb, block);
			if (!bh)
				continue;
			free_branches(inode, (sysv_zone_t*)bh->b_data,
					block_end(bh), depth);
			bforget(bh);
			sysv_free_block(sb, nr);
			mark_inode_dirty(inode);
		}
	} else
		free_data(inode, p, q);
}