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
struct file {int f_flags; struct file* private_data; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct file*) ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_NOCTTY ; 
 int O_TRUNC ; 
 int PTR_ERR (struct file*) ; 
 int /*<<< orphan*/  file_dentry (struct file*) ; 
 int /*<<< orphan*/  ovl_inode_realdata (struct inode*) ; 
 int ovl_maybe_copy_up (int /*<<< orphan*/ ,int) ; 
 struct file* ovl_open_realfile (struct file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ovl_open(struct inode *inode, struct file *file)
{
	struct file *realfile;
	int err;

	err = ovl_maybe_copy_up(file_dentry(file), file->f_flags);
	if (err)
		return err;

	/* No longer need these flags, so don't pass them on to underlying fs */
	file->f_flags &= ~(O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC);

	realfile = ovl_open_realfile(file, ovl_inode_realdata(inode));
	if (IS_ERR(realfile))
		return PTR_ERR(realfile);

	file->private_data = realfile;

	return 0;
}