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
struct iov_iter {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 long EINVAL ; 
 unsigned int SPLICE_F_ALL ; 
 scalar_t__ WRITE ; 
 int /*<<< orphan*/  iov_iter_count (struct iov_iter*) ; 
 scalar_t__ iov_iter_rw (struct iov_iter*) ; 
 scalar_t__ unlikely (unsigned int) ; 
 long vmsplice_to_pipe (struct file*,struct iov_iter*,unsigned int) ; 
 long vmsplice_to_user (struct file*,struct iov_iter*,unsigned int) ; 

__attribute__((used)) static long do_vmsplice(struct file *f, struct iov_iter *iter, unsigned int flags)
{
	if (unlikely(flags & ~SPLICE_F_ALL))
		return -EINVAL;

	if (!iov_iter_count(iter))
		return 0;

	if (iov_iter_rw(iter) == WRITE)
		return vmsplice_to_pipe(f, iter, flags);
	else
		return vmsplice_to_user(f, iter, flags);
}