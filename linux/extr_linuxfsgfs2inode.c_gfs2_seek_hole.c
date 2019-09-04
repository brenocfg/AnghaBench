#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {TYPE_1__* i_sb; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gl; } ;
struct gfs2_holder {int dummy; } ;
struct file {TYPE_2__* f_mapping; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_4__ {struct inode* host; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_maxbytes; } ;

/* Variables and functions */
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 int /*<<< orphan*/  LM_ST_SHARED ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (struct gfs2_holder*) ; 
 scalar_t__ gfs2_glock_nq_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_iomap_ops ; 
 int /*<<< orphan*/  inode_lock_shared (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock_shared (struct inode*) ; 
 scalar_t__ iomap_seek_hole (struct inode*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ vfs_setpos (struct file*,scalar_t__,int /*<<< orphan*/ ) ; 

loff_t gfs2_seek_hole(struct file *file, loff_t offset)
{
	struct inode *inode = file->f_mapping->host;
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_holder gh;
	loff_t ret;

	inode_lock_shared(inode);
	ret = gfs2_glock_nq_init(ip->i_gl, LM_ST_SHARED, 0, &gh);
	if (!ret)
		ret = iomap_seek_hole(inode, offset, &gfs2_iomap_ops);
	gfs2_glock_dq_uninit(&gh);
	inode_unlock_shared(inode);

	if (ret < 0)
		return ret;
	return vfs_setpos(file, ret, inode->i_sb->s_maxbytes);
}