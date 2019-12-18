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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct metapath {int mp_aheight; } ;
struct iomap {int addr; } ;
struct inode {int i_blkbits; } ;
typedef  int loff_t ;

/* Variables and functions */
 int gfs2_iomap_get (struct inode*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iomap*,struct metapath*) ; 
 int /*<<< orphan*/  i_blocksize (struct inode*) ; 
 int /*<<< orphan*/  release_metapath (struct metapath*) ; 

int gfs2_lblk_to_dblk(struct inode *inode, u32 lblock, u64 *dblock)
{
	struct iomap iomap = { };
	struct metapath mp = { .mp_aheight = 1, };
	loff_t pos = (loff_t)lblock << inode->i_blkbits;
	int ret;

	ret = gfs2_iomap_get(inode, pos, i_blocksize(inode), 0, &iomap, &mp);
	release_metapath(&mp);
	if (ret == 0)
		*dblock = iomap.addr >> inode->i_blkbits;

	return ret;
}