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
struct fuse_file {int flock; } ;
struct fuse_conn {scalar_t__ no_flock; } ;
struct file_lock {int dummy; } ;
struct file {struct fuse_file* private_data; } ;

/* Variables and functions */
 struct inode* file_inode (struct file*) ; 
 int fuse_setlk (struct file*,struct file_lock*,int) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 int locks_lock_file_wait (struct file*,struct file_lock*) ; 

__attribute__((used)) static int fuse_file_flock(struct file *file, int cmd, struct file_lock *fl)
{
	struct inode *inode = file_inode(file);
	struct fuse_conn *fc = get_fuse_conn(inode);
	int err;

	if (fc->no_flock) {
		err = locks_lock_file_wait(file, fl);
	} else {
		struct fuse_file *ff = file->private_data;

		/* emulate flock with POSIX locks */
		ff->flock = true;
		err = fuse_setlk(file, fl, 1);
	}

	return err;
}