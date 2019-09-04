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
struct kiocb {int ki_flags; } ;
struct iov_iter {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTBLK ; 
 int IOCB_DIRECT ; 
 int /*<<< orphan*/  generic_file_read_iter (struct kiocb*,struct iov_iter*) ; 
 int /*<<< orphan*/  gfs2_file_direct_read (struct kiocb*,struct iov_iter*) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static ssize_t gfs2_file_read_iter(struct kiocb *iocb, struct iov_iter *to)
{
	ssize_t ret;

	if (iocb->ki_flags & IOCB_DIRECT) {
		ret = gfs2_file_direct_read(iocb, to);
		if (likely(ret != -ENOTBLK))
			return ret;
		iocb->ki_flags &= ~IOCB_DIRECT;
	}
	return generic_file_read_iter(iocb, to);
}