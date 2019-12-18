#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mode; } ;
struct fd {TYPE_2__* file; } ;
struct dentry {struct inode* d_inode; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_5__ {struct dentry* dentry; } ;
struct TYPE_6__ {int f_flags; int f_mode; TYPE_1__ f_path; } ;

/* Variables and functions */
 int ATTR_CTIME ; 
 int ATTR_MTIME ; 
 int EBADF ; 
 int EINVAL ; 
 int EPERM ; 
 int FMODE_WRITE ; 
 scalar_t__ IS_APPEND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_NON_LFS ; 
 int O_LARGEFILE ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int do_truncate (struct dentry*,int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 struct fd fdget (unsigned int) ; 
 int /*<<< orphan*/  fdput (struct fd) ; 
 int /*<<< orphan*/  file_inode (TYPE_2__*) ; 
 int locks_verify_truncate (struct inode*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_end_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_start_write (int /*<<< orphan*/ ) ; 
 int security_path_truncate (TYPE_1__*) ; 

long do_sys_ftruncate(unsigned int fd, loff_t length, int small)
{
	struct inode *inode;
	struct dentry *dentry;
	struct fd f;
	int error;

	error = -EINVAL;
	if (length < 0)
		goto out;
	error = -EBADF;
	f = fdget(fd);
	if (!f.file)
		goto out;

	/* explicitly opened as large or we are on 64-bit box */
	if (f.file->f_flags & O_LARGEFILE)
		small = 0;

	dentry = f.file->f_path.dentry;
	inode = dentry->d_inode;
	error = -EINVAL;
	if (!S_ISREG(inode->i_mode) || !(f.file->f_mode & FMODE_WRITE))
		goto out_putf;

	error = -EINVAL;
	/* Cannot ftruncate over 2^31 bytes without large file support */
	if (small && length > MAX_NON_LFS)
		goto out_putf;

	error = -EPERM;
	/* Check IS_APPEND on real upper inode */
	if (IS_APPEND(file_inode(f.file)))
		goto out_putf;

	sb_start_write(inode->i_sb);
	error = locks_verify_truncate(inode, f.file, length);
	if (!error)
		error = security_path_truncate(&f.file->f_path);
	if (!error)
		error = do_truncate(dentry, length, ATTR_MTIME|ATTR_CTIME, f.file);
	sb_end_write(inode->i_sb);
out_putf:
	fdput(f);
out:
	return error;
}