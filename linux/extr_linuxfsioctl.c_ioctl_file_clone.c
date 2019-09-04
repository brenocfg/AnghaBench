#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_5__ {scalar_t__ mnt; } ;
struct file {TYPE_2__ f_path; } ;
struct fd {TYPE_3__* file; } ;
struct TYPE_4__ {scalar_t__ mnt; } ;
struct TYPE_6__ {TYPE_1__ f_path; } ;

/* Variables and functions */
 long EBADF ; 
 int EXDEV ; 
 struct fd fdget (unsigned long) ; 
 int /*<<< orphan*/  fdput (struct fd) ; 
 int vfs_clone_file_range (TYPE_3__*,int /*<<< orphan*/ ,struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long ioctl_file_clone(struct file *dst_file, unsigned long srcfd,
			     u64 off, u64 olen, u64 destoff)
{
	struct fd src_file = fdget(srcfd);
	int ret;

	if (!src_file.file)
		return -EBADF;
	ret = -EXDEV;
	if (src_file.file->f_path.mnt != dst_file->f_path.mnt)
		goto fdput;
	ret = vfs_clone_file_range(src_file.file, off, dst_file, destoff, olen);
fdput:
	fdput(src_file);
	return ret;
}