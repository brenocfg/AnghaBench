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
typedef  int /*<<< orphan*/  u32 ;
struct kstat {int dummy; } ;
struct fd {TYPE_1__* file; } ;
struct TYPE_2__ {int /*<<< orphan*/  f_path; } ;

/* Variables and functions */
 int EBADF ; 
 int EINVAL ; 
 unsigned int KSTAT_QUERY_FLAGS ; 
 struct fd fdget_raw (unsigned int) ; 
 int /*<<< orphan*/  fdput (struct fd) ; 
 int vfs_getattr (int /*<<< orphan*/ *,struct kstat*,int /*<<< orphan*/ ,unsigned int) ; 

int vfs_statx_fd(unsigned int fd, struct kstat *stat,
		 u32 request_mask, unsigned int query_flags)
{
	struct fd f;
	int error = -EBADF;

	if (query_flags & ~KSTAT_QUERY_FLAGS)
		return -EINVAL;

	f = fdget_raw(fd);
	if (f.file) {
		error = vfs_getattr(&f.file->f_path, stat,
				    request_mask, query_flags);
		fdput(f);
	}
	return error;
}