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
typedef  int /*<<< orphan*/  umode_t ;
struct fd {TYPE_1__* file; } ;
struct TYPE_2__ {int /*<<< orphan*/  f_path; } ;

/* Variables and functions */
 int EBADF ; 
 int /*<<< orphan*/  audit_file (TYPE_1__*) ; 
 int chmod_common (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct fd fdget (unsigned int) ; 
 int /*<<< orphan*/  fdput (struct fd) ; 

int ksys_fchmod(unsigned int fd, umode_t mode)
{
	struct fd f = fdget(fd);
	int err = -EBADF;

	if (f.file) {
		audit_file(f.file);
		err = chmod_common(&f.file->f_path, mode);
		fdput(f);
	}
	return err;
}