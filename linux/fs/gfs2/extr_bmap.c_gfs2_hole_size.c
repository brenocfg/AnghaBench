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
struct metapath {int dummy; } ;
struct iomap {int length; } ;
struct inode {int i_blkbits; } ;
typedef  int sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFS2_SB (struct inode*) ; 
 int /*<<< orphan*/  clone_metapath (struct metapath*,struct metapath*) ; 
 int /*<<< orphan*/  gfs2_hole_walker ; 
 int gfs2_walk_metadata (struct inode*,struct metapath*,int,int /*<<< orphan*/ ) ; 
 int metapath_to_block (int /*<<< orphan*/ ,struct metapath*) ; 
 int /*<<< orphan*/  release_metapath (struct metapath*) ; 

__attribute__((used)) static int gfs2_hole_size(struct inode *inode, sector_t lblock, u64 len,
			  struct metapath *mp, struct iomap *iomap)
{
	struct metapath clone;
	u64 hole_size;
	int ret;

	clone_metapath(&clone, mp);
	ret = gfs2_walk_metadata(inode, &clone, len, gfs2_hole_walker);
	if (ret < 0)
		goto out;

	if (ret == 1)
		hole_size = metapath_to_block(GFS2_SB(inode), &clone) - lblock;
	else
		hole_size = len;
	iomap->length = hole_size << inode->i_blkbits;
	ret = 0;

out:
	release_metapath(&clone);
	return ret;
}