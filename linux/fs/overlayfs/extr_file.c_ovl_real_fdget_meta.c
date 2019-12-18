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
struct inode {int dummy; } ;
struct file {int f_flags; struct file const* private_data; } ;
struct fd {struct file const* file; scalar_t__ flags; } ;

/* Variables and functions */
 scalar_t__ FDPUT_FPUT ; 
 int O_NOATIME ; 
 int PTR_ERR_OR_ZERO (struct file const*) ; 
 struct inode* file_inode (struct file const*) ; 
 int ovl_change_flags (struct file const*,int) ; 
 struct inode* ovl_inode_real (struct inode*) ; 
 struct inode* ovl_inode_realdata (struct inode*) ; 
 struct file const* ovl_open_realfile (struct file const*,struct inode*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ovl_real_fdget_meta(const struct file *file, struct fd *real,
			       bool allow_meta)
{
	struct inode *inode = file_inode(file);
	struct inode *realinode;

	real->flags = 0;
	real->file = file->private_data;

	if (allow_meta)
		realinode = ovl_inode_real(inode);
	else
		realinode = ovl_inode_realdata(inode);

	/* Has it been copied up since we'd opened it? */
	if (unlikely(file_inode(real->file) != realinode)) {
		real->flags = FDPUT_FPUT;
		real->file = ovl_open_realfile(file, realinode);

		return PTR_ERR_OR_ZERO(real->file);
	}

	/* Did the flags change since open? */
	if (unlikely((file->f_flags ^ real->file->f_flags) & ~O_NOATIME))
		return ovl_change_flags(real->file, file->f_flags);

	return 0;
}