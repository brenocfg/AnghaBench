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
struct kstatfs {int dummy; } ;
struct fd {TYPE_1__* file; } ;
struct TYPE_2__ {int /*<<< orphan*/  f_path; } ;

/* Variables and functions */
 int EBADF ; 
 struct fd fdget_raw (int) ; 
 int /*<<< orphan*/  fdput (struct fd) ; 
 int vfs_statfs (int /*<<< orphan*/ *,struct kstatfs*) ; 

int fd_statfs(int fd, struct kstatfs *st)
{
	struct fd f = fdget_raw(fd);
	int error = -EBADF;
	if (f.file) {
		error = vfs_statfs(&f.file->f_path, st);
		fdput(f);
	}
	return error;
}