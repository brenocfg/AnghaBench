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
struct fuse_file {struct fuse_conn* fc; } ;
struct fuse_conn {int dummy; } ;
struct file {int /*<<< orphan*/  f_flags; struct fuse_file* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  fuse_conn_put (struct fuse_conn*) ; 
 int /*<<< orphan*/  fuse_sync_release (int /*<<< orphan*/ *,struct fuse_file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cuse_release(struct inode *inode, struct file *file)
{
	struct fuse_file *ff = file->private_data;
	struct fuse_conn *fc = ff->fc;

	fuse_sync_release(NULL, ff, file->f_flags);
	fuse_conn_put(fc);

	return 0;
}