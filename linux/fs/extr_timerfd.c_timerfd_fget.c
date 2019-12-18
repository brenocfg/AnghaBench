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
struct fd {TYPE_1__* file; } ;
struct TYPE_2__ {int /*<<< orphan*/ * f_op; } ;

/* Variables and functions */
 int EBADF ; 
 int EINVAL ; 
 struct fd fdget (int) ; 
 int /*<<< orphan*/  fdput (struct fd) ; 
 int /*<<< orphan*/  timerfd_fops ; 

__attribute__((used)) static int timerfd_fget(int fd, struct fd *p)
{
	struct fd f = fdget(fd);
	if (!f.file)
		return -EBADF;
	if (f.file->f_op != &timerfd_fops) {
		fdput(f);
		return -EINVAL;
	}
	*p = f;
	return 0;
}