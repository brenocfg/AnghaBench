#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct fd {TYPE_2__* file; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_7__ {int /*<<< orphan*/  i_mode; } ;
struct TYPE_6__ {int f_mode; TYPE_1__* f_mapping; } ;
struct TYPE_5__ {int /*<<< orphan*/  a_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  EINVAL ; 
 int FMODE_READ ; 
 int /*<<< orphan*/  POSIX_FADV_WILLNEED ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 struct fd fdget (int) ; 
 int /*<<< orphan*/  fdput (struct fd) ; 
 TYPE_3__* file_inode (TYPE_2__*) ; 
 int /*<<< orphan*/  vfs_fadvise (TYPE_2__*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

ssize_t ksys_readahead(int fd, loff_t offset, size_t count)
{
	ssize_t ret;
	struct fd f;

	ret = -EBADF;
	f = fdget(fd);
	if (!f.file || !(f.file->f_mode & FMODE_READ))
		goto out;

	/*
	 * The readahead() syscall is intended to run only on files
	 * that can execute readahead. If readahead is not possible
	 * on this file, then we must return -EINVAL.
	 */
	ret = -EINVAL;
	if (!f.file->f_mapping || !f.file->f_mapping->a_ops ||
	    !S_ISREG(file_inode(f.file)->i_mode))
		goto out;

	ret = vfs_fadvise(f.file, offset, count, POSIX_FADV_WILLNEED);
out:
	fdput(f);
	return ret;
}