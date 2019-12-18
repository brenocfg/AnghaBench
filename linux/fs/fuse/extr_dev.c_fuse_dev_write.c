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
struct kiocb {int /*<<< orphan*/  ki_filp; } ;
struct iov_iter {int dummy; } ;
struct fuse_dev {int dummy; } ;
struct fuse_copy_state {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EPERM ; 
 int /*<<< orphan*/  fuse_copy_init (struct fuse_copy_state*,int /*<<< orphan*/ ,struct iov_iter*) ; 
 int /*<<< orphan*/  fuse_dev_do_write (struct fuse_dev*,struct fuse_copy_state*,int /*<<< orphan*/ ) ; 
 struct fuse_dev* fuse_get_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iov_iter_count (struct iov_iter*) ; 
 int /*<<< orphan*/  iter_is_iovec (struct iov_iter*) ; 

__attribute__((used)) static ssize_t fuse_dev_write(struct kiocb *iocb, struct iov_iter *from)
{
	struct fuse_copy_state cs;
	struct fuse_dev *fud = fuse_get_dev(iocb->ki_filp);

	if (!fud)
		return -EPERM;

	if (!iter_is_iovec(from))
		return -EINVAL;

	fuse_copy_init(&cs, 0, from);

	return fuse_dev_do_write(fud, &cs, iov_iter_count(from));
}