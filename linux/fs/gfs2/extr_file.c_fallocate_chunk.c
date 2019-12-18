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
struct iomap {scalar_t__ offset; int length; int flags; int addr; } ;
struct inode {int i_blkbits; struct super_block* i_sb; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gl; } ;
struct buffer_head {int dummy; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 int /*<<< orphan*/  GFS2_SB (struct inode*) ; 
 int IOMAP_F_NEW ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  fs_err (int /*<<< orphan*/ ,char*) ; 
 int gfs2_iomap_get_alloc (struct inode*,scalar_t__,scalar_t__,struct iomap*) ; 
 scalar_t__ gfs2_is_stuffed (struct gfs2_inode*) ; 
 int gfs2_meta_inode_buffer (struct gfs2_inode*,struct buffer_head**) ; 
 int /*<<< orphan*/  gfs2_trans_add_meta (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int gfs2_unstuff_dinode (struct gfs2_inode*,int /*<<< orphan*/ *) ; 
 int sb_issue_zeroout (struct super_block*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int fallocate_chunk(struct inode *inode, loff_t offset, loff_t len,
			   int mode)
{
	struct super_block *sb = inode->i_sb;
	struct gfs2_inode *ip = GFS2_I(inode);
	loff_t end = offset + len;
	struct buffer_head *dibh;
	int error;

	error = gfs2_meta_inode_buffer(ip, &dibh);
	if (unlikely(error))
		return error;

	gfs2_trans_add_meta(ip->i_gl, dibh);

	if (gfs2_is_stuffed(ip)) {
		error = gfs2_unstuff_dinode(ip, NULL);
		if (unlikely(error))
			goto out;
	}

	while (offset < end) {
		struct iomap iomap = { };

		error = gfs2_iomap_get_alloc(inode, offset, end - offset,
					     &iomap);
		if (error)
			goto out;
		offset = iomap.offset + iomap.length;
		if (!(iomap.flags & IOMAP_F_NEW))
			continue;
		error = sb_issue_zeroout(sb, iomap.addr >> inode->i_blkbits,
					 iomap.length >> inode->i_blkbits,
					 GFP_NOFS);
		if (error) {
			fs_err(GFS2_SB(inode), "Failed to zero data buffers\n");
			goto out;
		}
	}
out:
	brelse(dibh);
	return error;
}