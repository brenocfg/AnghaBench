#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct path {int dummy; } ;
struct kiocb {struct file* ki_filp; } ;
struct iov_iter {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dentry; } ;
struct file {TYPE_1__ f_path; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 struct path* ecryptfs_dentry_to_lower_path (int /*<<< orphan*/ ) ; 
 scalar_t__ generic_file_read_iter (struct kiocb*,struct iov_iter*) ; 
 int /*<<< orphan*/  touch_atime (struct path*) ; 

__attribute__((used)) static ssize_t ecryptfs_read_update_atime(struct kiocb *iocb,
				struct iov_iter *to)
{
	ssize_t rc;
	struct path *path;
	struct file *file = iocb->ki_filp;

	rc = generic_file_read_iter(iocb, to);
	if (rc >= 0) {
		path = ecryptfs_dentry_to_lower_path(file->f_path.dentry);
		touch_atime(path);
	}
	return rc;
}