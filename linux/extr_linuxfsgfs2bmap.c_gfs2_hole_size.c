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
typedef  int /*<<< orphan*/  u64 ;
struct metapath {int dummy; } ;
struct iomap {int length; } ;
struct inode {int i_blkbits; } ;
struct gfs2_hole_walker_args {int blocks; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  gfs2_hole_walker ; 
 int gfs2_walk_metadata (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct metapath*,int /*<<< orphan*/ ,struct gfs2_hole_walker_args*) ; 

__attribute__((used)) static int gfs2_hole_size(struct inode *inode, sector_t lblock, u64 len,
			  struct metapath *mp, struct iomap *iomap)
{
	struct gfs2_hole_walker_args args = { };
	int ret = 0;

	ret = gfs2_walk_metadata(inode, lblock, len, mp, gfs2_hole_walker, &args);
	if (!ret)
		iomap->length = args.blocks << inode->i_blkbits;
	return ret;
}