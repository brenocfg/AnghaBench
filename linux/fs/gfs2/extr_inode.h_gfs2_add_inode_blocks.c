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
struct inode {scalar_t__ i_blocks; scalar_t__ i_blkbits; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 scalar_t__ GFS2_BASIC_BLOCK_SHIFT ; 
 int /*<<< orphan*/  GFS2_SB (struct inode*) ; 
 int /*<<< orphan*/  gfs2_assert (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void gfs2_add_inode_blocks(struct inode *inode, s64 change)
{
	change <<= inode->i_blkbits - GFS2_BASIC_BLOCK_SHIFT;
	gfs2_assert(GFS2_SB(inode), (change >= 0 || inode->i_blocks >= -change));
	inode->i_blocks += change;
}