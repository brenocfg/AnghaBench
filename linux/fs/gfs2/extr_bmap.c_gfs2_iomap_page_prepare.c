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
struct iomap {int dummy; } ;
struct inode {unsigned int i_blkbits; } ;
struct gfs2_sbd {int dummy; } ;
typedef  unsigned int loff_t ;

/* Variables and functions */
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 scalar_t__ RES_DINODE ; 
 int gfs2_trans_begin (struct gfs2_sbd*,scalar_t__,int /*<<< orphan*/ ) ; 
 int i_blocksize (struct inode*) ; 

__attribute__((used)) static int gfs2_iomap_page_prepare(struct inode *inode, loff_t pos,
				   unsigned len, struct iomap *iomap)
{
	unsigned int blockmask = i_blocksize(inode) - 1;
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	unsigned int blocks;

	blocks = ((pos & blockmask) + len + blockmask) >> inode->i_blkbits;
	return gfs2_trans_begin(sdp, RES_DINODE + blocks, 0);
}