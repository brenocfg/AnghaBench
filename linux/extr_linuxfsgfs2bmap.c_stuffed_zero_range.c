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
struct inode {scalar_t__ i_size; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gl; } ;
struct gfs2_dinode {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int gfs2_meta_inode_buffer (struct gfs2_inode*,struct buffer_head**) ; 
 int /*<<< orphan*/  gfs2_trans_add_meta (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int stuffed_zero_range(struct inode *inode, loff_t offset, loff_t length)
{
	struct gfs2_inode *ip = GFS2_I(inode);
	struct buffer_head *dibh;
	int error;

	if (offset >= inode->i_size)
		return 0;
	if (offset + length > inode->i_size)
		length = inode->i_size - offset;

	error = gfs2_meta_inode_buffer(ip, &dibh);
	if (error)
		return error;
	gfs2_trans_add_meta(ip->i_gl, dibh);
	memset(dibh->b_data + sizeof(struct gfs2_dinode) + offset, 0,
	       length);
	brelse(dibh);
	return 0;
}