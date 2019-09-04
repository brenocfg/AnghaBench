#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uid_t ;
struct fd {TYPE_1__* file; } ;
typedef  int /*<<< orphan*/  gid_t ;
struct TYPE_4__ {int /*<<< orphan*/  f_path; } ;

/* Variables and functions */
 int EBADF ; 
 int /*<<< orphan*/  audit_file (TYPE_1__*) ; 
 int chown_common (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fd fdget (unsigned int) ; 
 int /*<<< orphan*/  fdput (struct fd) ; 
 int /*<<< orphan*/  mnt_drop_write_file (TYPE_1__*) ; 
 int mnt_want_write_file (TYPE_1__*) ; 

int ksys_fchown(unsigned int fd, uid_t user, gid_t group)
{
	struct fd f = fdget(fd);
	int error = -EBADF;

	if (!f.file)
		goto out;

	error = mnt_want_write_file(f.file);
	if (error)
		goto out_fput;
	audit_file(f.file);
	error = chown_common(&f.file->f_path, user, group);
	mnt_drop_write_file(f.file);
out_fput:
	fdput(f);
out:
	return error;
}